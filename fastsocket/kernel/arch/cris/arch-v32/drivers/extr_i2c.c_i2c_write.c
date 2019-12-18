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
 int /*<<< orphan*/  i2c_getack () ; 
 int /*<<< orphan*/  i2c_lock ; 
 int /*<<< orphan*/  i2c_outbyte (unsigned char) ; 
 int /*<<< orphan*/  i2c_start () ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
i2c_write(unsigned char theSlave, void *data, size_t nbytes)
{
	int error, cntr = 3;
	unsigned char bytes_wrote = 0;
	unsigned char value;
	unsigned long flags;

	spin_lock_irqsave(&i2c_lock, flags);

	do {
		error = 0;

		i2c_start();
		/*
		 * send slave address
		 */
		i2c_outbyte((theSlave & 0xfe));
		/*
		 * wait for ack
		 */
		if (!i2c_getack())
			error = 1;
		/*
		 * send data
		 */
		for (bytes_wrote = 0; bytes_wrote < nbytes; bytes_wrote++) {
			memcpy(&value, data + bytes_wrote, sizeof value);
			i2c_outbyte(value);
			/*
			 * now it's time to wait for ack
			 */
			if (!i2c_getack())
				error |= 4;
		}
		/*
		 * end byte stream
		 */
		i2c_stop();

	} while (error && cntr--);

	i2c_delay(CLOCK_LOW_TIME);

	spin_unlock_irqrestore(&i2c_lock, flags);

	return -error;
}