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
typedef  int u32 ;
typedef  int u16 ;
struct maestro {int io; int tuned; int stereo; scalar_t__ muted; } ;

/* Variables and functions */
 int IO_MASK ; 
 int STR_CLK ; 
 int STR_DATA ; 
 int STR_MOST ; 
 int STR_WREN ; 
 int inw (int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 radio_bits_get(struct maestro *dev)
{
	u16 io = dev->io, l, rdata;
	u32 data = 0;
	u16 omask;

	omask = inw(io + IO_MASK);
	outw(~(STR_CLK | STR_WREN), io + IO_MASK);
	outw(0, io);
	udelay(16);

	for (l = 24; l--;) {
		outw(STR_CLK, io);		/* HI state */
		udelay(2);
		if (!l)
			dev->tuned = inw(io) & STR_MOST ? 0 : 0xffff;
		outw(0, io);			/* LO state */
		udelay(2);
		data <<= 1;			/* shift data */
		rdata = inw(io);
		if (!l)
			dev->stereo = (rdata & STR_MOST) ?  0 : 1;
		else if (rdata & STR_DATA)
			data++;
		udelay(2);
	}

	if (dev->muted)
		outw(STR_WREN, io);

	udelay(4);
	outw(omask, io + IO_MASK);

	return data & 0x3ffe;
}