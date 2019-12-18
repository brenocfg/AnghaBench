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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  io_delay () ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void beep(unsigned int hz)
{
	u8 enable;

	if (!hz) {
		enable = 0x00;		/* Turn off speaker */
	} else {
		u16 div = 1193181/hz;

		outb(0xb6, 0x43);	/* Ctr 2, squarewave, load, binary */
		io_delay();
		outb(div, 0x42);	/* LSB of counter */
		io_delay();
		outb(div >> 8, 0x42);	/* MSB of counter */
		io_delay();

		enable = 0x03;		/* Turn on speaker */
	}
	inb(0x61);		/* Dummy read of System Control Port B */
	io_delay();
	outb(enable, 0x61);	/* Enable timer 2 output to speaker */
	io_delay();
}