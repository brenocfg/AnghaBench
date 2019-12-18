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
struct ubifs_lprops {int flags; scalar_t__ free; scalar_t__ dirty; } ;
struct ubifs_info {scalar_t__ leb_size; scalar_t__ min_idx_node_sz; scalar_t__ dead_wm; } ;

/* Variables and functions */
 int LPROPS_DIRTY ; 
 int LPROPS_DIRTY_IDX ; 
 int LPROPS_EMPTY ; 
 int LPROPS_FRDI_IDX ; 
 int LPROPS_FREE ; 
 int LPROPS_FREEABLE ; 
 int LPROPS_INDEX ; 
 int LPROPS_TAKEN ; 
 int LPROPS_UNCAT ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

int ubifs_categorize_lprops(const struct ubifs_info *c,
			    const struct ubifs_lprops *lprops)
{
	if (lprops->flags & LPROPS_TAKEN)
		return LPROPS_UNCAT;

	if (lprops->free == c->leb_size) {
		ubifs_assert(!(lprops->flags & LPROPS_INDEX));
		return LPROPS_EMPTY;
	}

	if (lprops->free + lprops->dirty == c->leb_size) {
		if (lprops->flags & LPROPS_INDEX)
			return LPROPS_FRDI_IDX;
		else
			return LPROPS_FREEABLE;
	}

	if (lprops->flags & LPROPS_INDEX) {
		if (lprops->dirty + lprops->free >= c->min_idx_node_sz)
			return LPROPS_DIRTY_IDX;
	} else {
		if (lprops->dirty >= c->dead_wm &&
		    lprops->dirty > lprops->free)
			return LPROPS_DIRTY;
		if (lprops->free > 0)
			return LPROPS_FREE;
	}

	return LPROPS_UNCAT;
}