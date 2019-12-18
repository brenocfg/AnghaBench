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
struct cadet {int curtuner; int tunestat; scalar_t__ sigstrength; int /*<<< orphan*/  lock; scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  cadet_gettune (struct cadet*) ; 
 int /*<<< orphan*/  cadet_settune (struct cadet*,unsigned int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__** sigtable ; 

__attribute__((used)) static void cadet_setfreq(struct cadet *dev, unsigned freq)
{
	unsigned fifo;
	int i, j, test;
	int curvol;

	/*
	 * Formulate a fifo command
	 */
	fifo = 0;
	if (dev->curtuner == 0) {    /* FM */
		test = 102400;
		freq = (freq * 1000) / 16;       /* Make it kHz */
		freq += 10700;               /* IF is 10700 kHz */
		for (i = 0; i < 14; i++) {
			fifo = fifo << 1;
			if (freq >= test) {
				fifo |= 0x01;
				freq -= test;
			}
			test = test >> 1;
		}
	}
	if (dev->curtuner == 1) {    /* AM */
		fifo = (freq / 16) + 2010;            /* Make it kHz */
		fifo |= 0x100000;            /* Select AM Band */
	}

	/*
	 * Save current volume/mute setting
	 */

	mutex_lock(&dev->lock);
	outb(7, dev->io);                /* Select tuner control */
	curvol = inb(dev->io + 1);
	mutex_unlock(&dev->lock);

	/*
	 * Tune the card
	 */
	for (j = 3; j > -1; j--) {
		cadet_settune(dev, fifo | (j << 16));

		mutex_lock(&dev->lock);
		outb(7, dev->io);         /* Select tuner control */
		outb(curvol, dev->io + 1);
		mutex_unlock(&dev->lock);

		msleep(100);

		cadet_gettune(dev);
		if ((dev->tunestat & 0x40) == 0) {   /* Tuned */
			dev->sigstrength = sigtable[dev->curtuner][j];
			return;
		}
	}
	dev->sigstrength = 0;
}