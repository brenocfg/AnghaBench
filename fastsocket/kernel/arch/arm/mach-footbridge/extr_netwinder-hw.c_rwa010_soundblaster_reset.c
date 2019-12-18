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
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int inb (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rwa010_soundblaster_reset(void)
{
	int i;

	outb(1, 0x226);
	udelay(3);
	outb(0, 0x226);

	for (i = 0; i < 5; i++) {
		if (inb(0x22e) & 0x80)
			break;
		mdelay(1);
	}
	if (i == 5)
		printk("SoundBlaster: DSP reset failed\n");

	dprintk("SoundBlaster DSP reset: %02X (AA)\n", inb(0x22a));

	for (i = 0; i < 5; i++) {
		if ((inb(0x22c) & 0x80) == 0)
			break;
		mdelay(1);
	}

	if (i == 5)
		printk("SoundBlaster: DSP not ready\n");
	else {
		outb(0xe1, 0x22c);

		dprintk("SoundBlaster DSP id: ");
		i = inb(0x22a);
		udelay(1);
		i |= inb(0x22a) << 8;
		dprintk("%04X\n", i);

		for (i = 0; i < 5; i++) {
			if ((inb(0x22c) & 0x80) == 0)
				break;
			mdelay(1);
		}

		if (i == 5)
			printk("SoundBlaster: could not turn speaker off\n");

		outb(0xd3, 0x22c);
	}

	/* turn on OPL3 */
	outb(5, 0x38a);
	outb(1, 0x38b);
}