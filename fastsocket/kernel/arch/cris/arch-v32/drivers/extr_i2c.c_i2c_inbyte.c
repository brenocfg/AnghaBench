#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int CLOCK_HIGH_TIME ; 
 int CLOCK_LOW_TIME ; 
 int /*<<< orphan*/  I2C_CLOCK_HIGH ; 
 int /*<<< orphan*/  I2C_CLOCK_LOW ; 
 int /*<<< orphan*/  i2c_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_delay (int) ; 
 int /*<<< orphan*/  i2c_dir_in () ; 
 int /*<<< orphan*/  i2c_disable () ; 
 int /*<<< orphan*/  i2c_enable () ; 
 unsigned char i2c_getbit () ; 

unsigned char
i2c_inbyte(void)
{
	unsigned char aBitByte = 0;
	int i;

	/* Switch off I2C to get bit */
	i2c_disable();
	i2c_dir_in();
	i2c_delay(CLOCK_HIGH_TIME/2);

	/* Get bit */
	aBitByte |= i2c_getbit();

	/* Enable I2C */
	i2c_enable();
	i2c_delay(CLOCK_LOW_TIME/2);

	for (i = 1; i < 8; i++) {
		aBitByte <<= 1;
		/* Clock pulse */
		i2c_clk(I2C_CLOCK_HIGH);
		i2c_delay(CLOCK_HIGH_TIME);
		i2c_clk(I2C_CLOCK_LOW);
		i2c_delay(CLOCK_LOW_TIME);

		/* Switch off I2C to get bit */
		i2c_disable();
		i2c_dir_in();
		i2c_delay(CLOCK_HIGH_TIME/2);

		/* Get bit */
		aBitByte |= i2c_getbit();

		/* Enable I2C */
		i2c_enable();
		i2c_delay(CLOCK_LOW_TIME/2);
	}
	i2c_clk(I2C_CLOCK_HIGH);
	i2c_delay(CLOCK_HIGH_TIME);

	/*
	 * we leave the clock low, getbyte is usually followed
	 * by sendack/nack, they assume the clock to be low
	 */
	i2c_clk(I2C_CLOCK_LOW);
	return aBitByte;
}