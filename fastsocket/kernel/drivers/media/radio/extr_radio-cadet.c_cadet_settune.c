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
struct cadet {int /*<<< orphan*/  lock; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void cadet_settune(struct cadet *dev, unsigned fifo)
{
	int i;
	unsigned test;

	mutex_lock(&dev->lock);

	outb(7, dev->io);                /* Select tuner control */
	/*
	 * Write the shift register
	 */
	test = 0;
	test = (fifo >> 23) & 0x02;      /* Align data for SDO */
	test |= 0x1c;                /* SDM=1, SWE=1, SEN=1, SCK=0 */
	outb(7, dev->io);                /* Select tuner control */
	outb(test, dev->io + 1);           /* Initialize for write */
	for (i = 0; i < 25; i++) {
		test |= 0x01;              /* Toggle SCK High */
		outb(test, dev->io + 1);
		test &= 0xfe;              /* Toggle SCK Low */
		outb(test, dev->io + 1);
		fifo = fifo << 1;            /* Prepare the next bit */
		test = 0x1c | ((fifo >> 23) & 0x02);
		outb(test, dev->io + 1);
	}
	mutex_unlock(&dev->lock);
}