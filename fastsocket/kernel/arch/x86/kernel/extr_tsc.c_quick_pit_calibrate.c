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
typedef  unsigned long u64 ;

/* Variables and functions */
 int MAX_QUICK_PIT_ITERATIONS ; 
 unsigned long PIT_TICK_RATE ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 scalar_t__ pit_expect_msb (int,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  pit_verify_msb (int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static unsigned long quick_pit_calibrate(void)
{
	int i;
	u64 tsc, delta;
	unsigned long d1, d2;

	/* Set the Gate high, disable speaker */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Counter 2, mode 0 (one-shot), binary count
	 *
	 * NOTE! Mode 2 decrements by two (and then the
	 * output is flipped each time, giving the same
	 * final output frequency as a decrement-by-one),
	 * so mode 0 is much better when looking at the
	 * individual counts.
	 */
	outb(0xb0, 0x43);

	/* Start at 0xffff */
	outb(0xff, 0x42);
	outb(0xff, 0x42);

	/*
	 * The PIT starts counting at the next edge, so we
	 * need to delay for a microsecond. The easiest way
	 * to do that is to just read back the 16-bit counter
	 * once from the PIT.
	 */
	pit_verify_msb(0);

	if (pit_expect_msb(0xff, &tsc, &d1)) {
		for (i = 1; i <= MAX_QUICK_PIT_ITERATIONS; i++) {
			if (!pit_expect_msb(0xff-i, &delta, &d2))
				break;

			/*
			 * Iterate until the error is less than 500 ppm
			 */
			delta -= tsc;
			if (d1+d2 >= delta >> 11)
				continue;

			/*
			 * Check the PIT one more time to verify that
			 * all TSC reads were stable wrt the PIT.
			 *
			 * This also guarantees serialization of the
			 * last cycle read ('d2') in pit_expect_msb.
			 */
			if (!pit_verify_msb(0xfe - i))
				break;
			goto success;
		}
	}
	printk("Fast TSC calibration failed\n");
	return 0;

success:
	/*
	 * Ok, if we get here, then we've seen the
	 * MSB of the PIT decrement 'i' times, and the
	 * error has shrunk to less than 500 ppm.
	 *
	 * As a result, we can depend on there not being
	 * any odd delays anywhere, and the TSC reads are
	 * reliable (within the error).
	 *
	 * kHz = ticks / time-in-seconds / 1000;
	 * kHz = (t2 - t1) / (I * 256 / PIT_TICK_RATE) / 1000
	 * kHz = ((t2 - t1) * PIT_TICK_RATE) / (I * 256 * 1000)
	 */
	delta *= PIT_TICK_RATE;
	do_div(delta, i*256*1000);
	printk("Fast TSC calibration using PIT\n");
	return delta;
}