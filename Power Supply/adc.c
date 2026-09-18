void initADC() {
	ADMUX |= 1 << REFS0; // set ref. voltage to AVcc
	ADMUX |= 1 << ADLAR; // left justify output
	
	// channel set in 4 LSBs of ADMUX. 0000 for chan0
	ADCSRA |= 7; // set clock prescaler to 128
	ADCSRA |= 1 << ADEN; // enable ADC
}

uint8_t readADC(uint8_t channel) {
	channel &= 0x0f;
	ADMUX &= 0xf0;
	ADMUX |= channel; // choose channel
	ADCSRA |= 1 << ADSC; // start conversion
	while (ADCSRA & (1 << ADSC)); // wait for conversion to finish
	return ADCH;
}

