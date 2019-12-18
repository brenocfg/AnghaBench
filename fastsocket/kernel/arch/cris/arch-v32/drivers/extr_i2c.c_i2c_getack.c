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
 int I2C_CLOCK_HIGH ; 
 int I2C_CLOCK_LOW ; 
 int I2C_DATA_HIGH ; 
 int I2C_DATA_LOW ; 
 int /*<<< orphan*/  i2c_clk (int) ; 
 int /*<<< orphan*/  i2c_data (int) ; 
 int /*<<< orphan*/  i2c_delay (int) ; 
 int /*<<< orphan*/  i2c_dir_in () ; 
 int /*<<< orphan*/  i2c_dir_out () ; 
 int /*<<< orphan*/  i2c_disable () ; 
 int /*<<< orphan*/  i2c_enable () ; 
 scalar_t__ i2c_getbit () ; 

int
i2c_getack(void)
{
	int ack = 1;
	/*
	 * enable output
	 */
	i2c_dir_out();
	/*
	 * Release data bus by setting
	 * data high
	 */
	i2c_data(I2C_DATA_HIGH);
	/*
	 * enable input
	 */
	i2c_dir_in();
	i2c_delay(CLOCK_HIGH_TIME/4);
	/*
	 * generate ACK clock pulse
	 */
	i2c_clk(I2C_CLOCK_HIGH);
#if 0
	/*
	 * Use PORT PB instead of I2C
	 * for input. (I2C not working)
	 */
	i2c_clk(1);
	i2c_data(1);
	/*
	 * switch off I2C
	 */
	i2c_data(1);
	i2c_disable();
	i2c_dir_in();
#endif

	/*
	 * now wait for ack
	 */
	i2c_delay(CLOCK_HIGH_TIME/2);
	/*
	 * check for ack
	 */
	if (i2c_getbit())
		ack = 0;
	i2c_delay(CLOCK_HIGH_TIME/2);
	if (!ack) {
		if (!i2c_getbit()) /* receiver pulld SDA low */
			ack = 1;
		i2c_delay(CLOCK_HIGH_TIME/2);
	}

   /*
    * our clock is high now, make sure data is low
    * before we enable our output. If we keep data high
    * and enable output, we would generate a stop condition.
    */
#if 0
   i2c_data(I2C_DATA_LOW);

	/*
	 * end clock pulse
	 */
	i2c_enable();
	i2c_dir_out();
#endif
	i2c_clk(I2C_CLOCK_LOW);
	i2c_delay(CLOCK_HIGH_TIME/4);
	/*
	 * enable output
	 */
	i2c_dir_out();
	/*
	 * remove ACK clock pulse
	 */
	i2c_data(I2C_DATA_HIGH);
	i2c_delay(CLOCK_LOW_TIME/2);
	return ack;
}