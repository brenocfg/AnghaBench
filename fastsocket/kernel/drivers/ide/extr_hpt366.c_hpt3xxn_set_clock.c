#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {unsigned long extra_base; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 

__attribute__((used)) static void hpt3xxn_set_clock(ide_hwif_t *hwif, u8 mode)
{
	unsigned long base = hwif->extra_base;
	u8 scr2 = inb(base + 0x6b);

	if ((scr2 & 0x7f) == mode)
		return;

	/* Tristate the bus */
	outb(0x80, base + 0x63);
	outb(0x80, base + 0x67);

	/* Switch clock and reset channels */
	outb(mode, base + 0x6b);
	outb(0xc0, base + 0x69);

	/*
	 * Reset the state machines.
	 * NOTE: avoid accidentally enabling the disabled channels.
	 */
	outb(inb(base + 0x60) | 0x32, base + 0x60);
	outb(inb(base + 0x64) | 0x32, base + 0x64);

	/* Complete reset */
	outb(0x00, base + 0x69);

	/* Reconnect channels to bus */
	outb(0x00, base + 0x63);
	outb(0x00, base + 0x67);
}