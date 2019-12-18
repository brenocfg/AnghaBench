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
 int /*<<< orphan*/  i2c_getack () ; 
 unsigned char i2c_inbyte () ; 
 int /*<<< orphan*/  i2c_lock ; 
 int /*<<< orphan*/  i2c_outbyte (unsigned char) ; 
 int /*<<< orphan*/  i2c_sendack () ; 
 int /*<<< orphan*/  i2c_sendnack () ; 
 int /*<<< orphan*/  i2c_start () ; 
 int /*<<< orphan*/  i2c_stop () ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
i2c_read(unsigned char theSlave, void *data, size_t nbytes)
{
	unsigned char b = 0;
	unsigned char bytes_read = 0;
	int error, cntr = 3;
	unsigned long flags;

	spin_lock_irqsave(&i2c_lock, flags);

	do {
		error = 0;
		memset(data, 0, nbytes);
		/*
		 * generate start condition
		 */
		i2c_start();
		/*
		 * send slave address
		 */
		i2c_outbyte((theSlave | 0x01));
		/*
		 * wait for ack
		 */
		if (!i2c_getack())
			error = 1;
		/*
		 * fetch data
		 */
		for (bytes_read = 0; bytes_read < nbytes; bytes_read++) {
			b = i2c_inbyte();
			memcpy(data + bytes_read, &b, sizeof b);

			if (bytes_read < (nbytes - 1))
				i2c_sendack();
		}
		/*
		 * last received byte needs to be nacked
		 * instead of acked
		 */
		i2c_sendnack();
		/*
		 * end sequence
		 */
		i2c_stop();
	} while (error && cntr--);

	spin_unlock_irqrestore(&i2c_lock, flags);

	return -error;
}