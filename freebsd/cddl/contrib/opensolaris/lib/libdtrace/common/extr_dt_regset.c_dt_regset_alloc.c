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
typedef  size_t ulong_t ;
struct TYPE_3__ {size_t dr_size; unsigned long* dr_bitmap; } ;
typedef  TYPE_1__ dt_regset_t ;

/* Variables and functions */
 int BT_NBIPUL ; 
 int /*<<< orphan*/  BT_SET (size_t*,int) ; 
 size_t BT_ULMASK ; 
 size_t BT_ULSHIFT ; 
 int /*<<< orphan*/  D_NOREG ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 

int
dt_regset_alloc(dt_regset_t *drp)
{
	ulong_t nbits = drp->dr_size - 1;
	ulong_t maxw = nbits >> BT_ULSHIFT;
	ulong_t wx;

	for (wx = 0; wx <= maxw; wx++) {
		if (drp->dr_bitmap[wx] != ~0UL)
			break;
	}

	if (wx <= maxw) {
		ulong_t maxb = (wx == maxw) ? nbits & BT_ULMASK : BT_NBIPUL - 1;
		ulong_t word = drp->dr_bitmap[wx];
		ulong_t bit, bx;
		int reg;

		for (bit = 1, bx = 0; bx <= maxb; bx++, bit <<= 1) {
			if ((word & bit) == 0) {
				reg = (int)((wx << BT_ULSHIFT) | bx);
				BT_SET(drp->dr_bitmap, reg);
				return (reg);
			}
		}
	}

	xyerror(D_NOREG, "Insufficient registers to generate code");
	/*NOTREACHED*/
	return (-1);
}