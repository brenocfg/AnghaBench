#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int chunk_shift; int data_devs; int pi; int raid_devs; int io_inv_mask; TYPE_1__* raid_type; } ;
struct raid_set {TYPE_2__ set; } ;
struct raid_address {int di; int pi; int key; } ;
typedef  int sector_t ;
struct TYPE_3__ {int level; int /*<<< orphan*/  algorithm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  left_asym 134 
#define  left_sym 133 
#define  none 132 
#define  raid4 131 
#define  raid5 130 
#define  right_asym 129 
#define  right_sym 128 
 void* sector_div (int,int) ; 

__attribute__((used)) static struct raid_address *raid_address(struct raid_set *rs, sector_t sector,
					 struct raid_address *addr)
{
	sector_t stripe, tmp;

	/*
	 * chunk_number = sector / chunk_size
	 * stripe_number = chunk_number / data_devs
	 * di = stripe % data_devs;
	 */
	stripe = sector >> rs->set.chunk_shift;
	addr->di = sector_div(stripe, rs->set.data_devs);

	switch (rs->set.raid_type->level) {
	case raid4:
		addr->pi = rs->set.pi;
		goto check_shift_di;
	case raid5:
		tmp = stripe;
		addr->pi = sector_div(tmp, rs->set.raid_devs);

		switch (rs->set.raid_type->algorithm) {
		case left_asym:		/* Left asymmetric. */
			addr->pi = rs->set.data_devs - addr->pi;
		case right_asym:	/* Right asymmetric. */
check_shift_di:
			if (addr->di >= addr->pi)
				addr->di++;
			break;
		case left_sym:		/* Left symmetric. */
			addr->pi = rs->set.data_devs - addr->pi;
		case right_sym:		/* Right symmetric. */
			addr->di = (addr->pi + addr->di + 1) %
				   rs->set.raid_devs;
			break;
		case none: /* Ain't happen: RAID4 algorithm placeholder. */
			BUG();
		}
	}

	/*
	 * Start offset of the stripes chunk on any single device of the RAID
	 * set, adjusted in case io size differs from chunk size.
	 */
	addr->key = (stripe << rs->set.chunk_shift) +
		    (sector & rs->set.io_inv_mask);
	return addr;
}