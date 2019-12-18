#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int base; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ sb_dsp_reset (TYPE_1__*) ; 

__attribute__((used)) static void relocate_ess1688(sb_devc * devc)
{
	unsigned char bits;

	switch (devc->base)
	{
		case 0x220:
			bits = 0x04;
			break;
		case 0x230:
			bits = 0x05;
			break;
		case 0x240:
			bits = 0x06;
			break;
		case 0x250:
			bits = 0x07;
			break;
		default:
			return;	/* Wrong port */
	}

	DDB(printk("Doing ESS1688 address selection\n"));
	
	/*
	 * ES1688 supports two alternative ways for software address config.
	 * First try the so called Read-Sequence-Key method.
	 */

	/* Reset the sequence logic */
	inb(0x229);
	inb(0x229);
	inb(0x229);

	/* Perform the read sequence */
	inb(0x22b);
	inb(0x229);
	inb(0x22b);
	inb(0x229);
	inb(0x229);
	inb(0x22b);
	inb(0x229);

	/* Select the base address by reading from it. Then probe using the port. */
	inb(devc->base);
	if (sb_dsp_reset(devc))	/* Bingo */
		return;

#if 0				/* This causes system lockups (Nokia 386/25 at least) */
	/*
	 * The last resort is the system control register method.
	 */

	outb((0x00), 0xfb);	/* 0xFB is the unlock register */
	outb((0x00), 0xe0);	/* Select index 0 */
	outb((bits), 0xe1);	/* Write the config bits */
	outb((0x00), 0xf9);	/* 0xFB is the lock register */
#endif
}