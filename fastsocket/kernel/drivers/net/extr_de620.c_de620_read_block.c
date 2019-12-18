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
struct net_device {int dummy; } ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PORT ; 
 int DS0 ; 
 int DS1 ; 
 int NIC_Cmd ; 
 int /*<<< orphan*/  STATUS_PORT ; 
 int /*<<< orphan*/  de620_flip_ds (struct net_device*) ; 
 int /*<<< orphan*/  de620_read_byte (struct net_device*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int tot_cnt ; 

__attribute__((used)) static inline void
de620_read_block(struct net_device *dev, byte *data, int count)
{
#ifndef LOWSPEED
	byte value;
	byte uflip = NIC_Cmd ^ (DS0 | DS1);
	byte dflip = NIC_Cmd;
#else /* LOWSPEED */
#ifdef COUNT_LOOPS
	int bytes = count;

	tot_cnt = 0;
#endif /* COUNT_LOOPS */
#endif /* LOWSPEED */

#ifdef LOWSPEED
	/* No further optimization useful, the limit is in the adapter. */
	while (count-- > 0) {
		*data++ = de620_read_byte(dev);
		de620_flip_ds(dev);
	}
#ifdef COUNT_LOOPS
	/* trial debug output: loops per byte in de620_ready() */
	printk("READ(%d)\n", tot_cnt/(2*(bytes?bytes:1)));
#endif /* COUNT_LOOPS */
#else /* not LOWSPEED */
	while (count-- > 0) {
		value = inb(STATUS_PORT) & 0xf0; /* High nibble */
		outb(uflip, COMMAND_PORT);
		*data++ = value | inb(STATUS_PORT) >> 4; /* Low nibble */
		outb(dflip , COMMAND_PORT);
	}
#endif /* LOWSPEED */
}