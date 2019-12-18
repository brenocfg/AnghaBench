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
 unsigned char i2c_inbyte () ; 
 int /*<<< orphan*/  i2c_lock ; 
 int /*<<< orphan*/  i2c_outbyte (unsigned char) ; 
 int /*<<< orphan*/  i2c_sendnack () ; 
 int /*<<< orphan*/  i2c_start () ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

unsigned char
i2c_readreg(unsigned char theSlave, unsigned char theReg)
{
	unsigned char b = 0;
	int error, cntr = 3;
	unsigned long flags;

	spin_lock(&i2c_lock);

	do {
		error = 0;
		/*
		 * we don't like to be interrupted
		 */
		local_irq_save(flags);
		/*
		 * generate start condition
		 */
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
			error = 1;
		/*
		 * repeat start condition
		 */
		i2c_delay(CLOCK_LOW_TIME);
		i2c_start();
		/*
		 * send slave address
		 */
		i2c_outbyte(theSlave | 0x01);
		/*
		 * wait for ack
		 */
		if(!i2c_getack())
			error = 1;
		/*
		 * fetch register
		 */
		b = i2c_inbyte();
		/*
		 * last received byte needs to be nacked
		 * instead of acked
		 */
		i2c_sendnack();
		/*
		 * end sequence
		 */
		i2c_stop();
		/*
		 * enable interrupt again
		 */
		local_irq_restore(flags);
		
	} while(error && cntr--);

	spin_unlock(&i2c_lock);

	return b;
}