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
 int /*<<< orphan*/  CLOCK_LOW_TIME ; 
 int /*<<< orphan*/  i2c_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_dir_out () ; 
 int /*<<< orphan*/  i2c_getack () ; 
 int /*<<< orphan*/  i2c_lock ; 
 int /*<<< orphan*/  i2c_outbyte (unsigned char) ; 
 int /*<<< orphan*/  i2c_start () ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
i2c_writereg(unsigned char theSlave, unsigned char theReg, 
	     unsigned char theValue)
{
	int error, cntr = 3;
	unsigned long flags;

	spin_lock(&i2c_lock);

	do {
		error = 0;
		/*
		 * we don't like to be interrupted
		 */
		local_irq_save(flags);

		i2c_start();
		/*
		 * send slave address
		 */
		i2c_outbyte((theSlave & 0xfe));
		/*
		 * wait for ack
		 */
		if(!i2c_getack())
			error = 1;
		/*
		 * now select register
		 */
		i2c_dir_out();
		i2c_outbyte(theReg);
		/*
		 * now it's time to wait for ack
		 */
		if(!i2c_getack())
			error |= 2;
		/*
		 * send register register data
		 */
		i2c_outbyte(theValue);
		/*
		 * now it's time to wait for ack
		 */
		if(!i2c_getack())
			error |= 4;
		/*
		 * end byte stream
		 */
		i2c_stop();
		/*
		 * enable interrupt again
		 */
		local_irq_restore(flags);
		
	} while(error && cntr--);

	i2c_delay(CLOCK_LOW_TIME);

	spin_unlock(&i2c_lock);

	return -error;
}