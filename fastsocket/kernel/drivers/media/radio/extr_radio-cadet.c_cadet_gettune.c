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
struct cadet {int tunestat; int /*<<< orphan*/  lock; scalar_t__ io; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static unsigned cadet_gettune(struct cadet *dev)
{
	int curvol, i;
	unsigned fifo = 0;

	/*
	 * Prepare for read
	 */

	mutex_lock(&dev->lock);

	outb(7, dev->io);       /* Select tuner control */
	curvol = inb(dev->io + 1); /* Save current volume/mute setting */
	outb(0x00, dev->io + 1);  /* Ensure WRITE-ENABLE is LOW */
	dev->tunestat = 0xffff;

	/*
	 * Read the shift register
	 */
	for (i = 0; i < 25; i++) {
		fifo = (fifo << 1) | ((inb(dev->io + 1) >> 7) & 0x01);
		if (i < 24) {
			outb(0x01, dev->io + 1);
			dev->tunestat &= inb(dev->io + 1);
			outb(0x00, dev->io + 1);
		}
	}

	/*
	 * Restore volume/mute setting
	 */
	outb(curvol, dev->io + 1);
	mutex_unlock(&dev->lock);

	return fifo;
}