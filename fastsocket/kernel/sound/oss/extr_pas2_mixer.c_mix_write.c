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
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned char,scalar_t__) ; 
 int pas_model ; 
 scalar_t__ pas_translate_code ; 
 int /*<<< orphan*/  pas_write (unsigned char,int) ; 

void
mix_write(unsigned char data, int ioaddr)
{
	/*
	 * The Revision D cards have a problem with their MVA508 interface. The
	 * kludge-o-rama fix is to make a 16-bit quantity with identical LSB and
	 * MSBs out of the output byte and to do a 16-bit out to the mixer port -
	 * 1. We need to do this because it isn't timing problem but chip access
	 * sequence problem.
	 */

	if (pas_model == 4)
	  {
		  outw(data | (data << 8), (ioaddr + pas_translate_code) - 1);
		  outb((0x80), 0);
	} else
		pas_write(data, ioaddr);
}