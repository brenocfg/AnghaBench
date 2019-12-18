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
typedef  int /*<<< orphan*/  ushort ;

/* Variables and functions */
 int DRQ_ASSERTED ; 
 unsigned int MAXLOOP ; 
 int /*<<< orphan*/  REG2H (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_STATUS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (unsigned long) ; 
 int /*<<< orphan*/  udelay (long) ; 

__attribute__((used)) static int read_pio(unsigned long iobase, ushort * start, ushort * end)
{
	unsigned int loop = MAXLOOP;
	ushort *p;

	for (p = start; p <= end; p++) {
		while (!(inb(iobase + REG_STATUS) & DRQ_ASSERTED)) {
			udelay(1L);
			if (--loop == 0)
				return 1;
		}
		loop = MAXLOOP;
		*p = REG2H(inw(iobase));
	}

	return 0;
}