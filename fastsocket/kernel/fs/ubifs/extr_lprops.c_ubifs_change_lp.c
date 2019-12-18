#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct ubifs_lprops {int free; int dirty; int flags; int /*<<< orphan*/  lnum; } const ubifs_lprops ;
struct TYPE_2__ {scalar_t__ empty_lebs; scalar_t__ taken_empty_lebs; int total_free; int total_dirty; int total_dead; int total_dark; int total_used; int idx_lebs; } ;
struct ubifs_info {scalar_t__ main_lebs; scalar_t__ freeable_cnt; int leb_size; int dead_wm; int idx_gc_cnt; int /*<<< orphan*/  space_lock; TYPE_1__ lst; int /*<<< orphan*/  lp_mutex; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_INDEX ; 
 int LPROPS_NC ; 
 int LPROPS_TAKEN ; 
 int /*<<< orphan*/  change_category (struct ubifs_info*,struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_lp (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  is_lprops_dirty (struct ubifs_info*,struct ubifs_lprops const*) ; 
 int mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 scalar_t__ ubifs_calc_dark (struct ubifs_info*,int) ; 
 struct ubifs_lprops const* ubifs_lpt_lookup_dirty (struct ubifs_info*,int /*<<< orphan*/ ) ; 

const struct ubifs_lprops *ubifs_change_lp(struct ubifs_info *c,
					   const struct ubifs_lprops *lp,
					   int free, int dirty, int flags,
					   int idx_gc_cnt)
{
	/*
	 * This is the only function that is allowed to change lprops, so we
	 * discard the "const" qualifier.
	 */
	struct ubifs_lprops *lprops = (struct ubifs_lprops *)lp;

	dbg_lp("LEB %d, free %d, dirty %d, flags %d",
	       lprops->lnum, free, dirty, flags);

	ubifs_assert(mutex_is_locked(&c->lp_mutex));
	ubifs_assert(c->lst.empty_lebs >= 0 &&
		     c->lst.empty_lebs <= c->main_lebs);
	ubifs_assert(c->freeable_cnt >= 0);
	ubifs_assert(c->freeable_cnt <= c->main_lebs);
	ubifs_assert(c->lst.taken_empty_lebs >= 0);
	ubifs_assert(c->lst.taken_empty_lebs <= c->lst.empty_lebs);
	ubifs_assert(!(c->lst.total_free & 7) && !(c->lst.total_dirty & 7));
	ubifs_assert(!(c->lst.total_dead & 7) && !(c->lst.total_dark & 7));
	ubifs_assert(!(c->lst.total_used & 7));
	ubifs_assert(free == LPROPS_NC || free >= 0);
	ubifs_assert(dirty == LPROPS_NC || dirty >= 0);

	if (!is_lprops_dirty(c, lprops)) {
		lprops = ubifs_lpt_lookup_dirty(c, lprops->lnum);
		if (IS_ERR(lprops))
			return lprops;
	} else
		ubifs_assert(lprops == ubifs_lpt_lookup_dirty(c, lprops->lnum));

	ubifs_assert(!(lprops->free & 7) && !(lprops->dirty & 7));

	spin_lock(&c->space_lock);
	if ((lprops->flags & LPROPS_TAKEN) && lprops->free == c->leb_size)
		c->lst.taken_empty_lebs -= 1;

	if (!(lprops->flags & LPROPS_INDEX)) {
		int old_spc;

		old_spc = lprops->free + lprops->dirty;
		if (old_spc < c->dead_wm)
			c->lst.total_dead -= old_spc;
		else
			c->lst.total_dark -= ubifs_calc_dark(c, old_spc);

		c->lst.total_used -= c->leb_size - old_spc;
	}

	if (free != LPROPS_NC) {
		free = ALIGN(free, 8);
		c->lst.total_free += free - lprops->free;

		/* Increase or decrease empty LEBs counter if needed */
		if (free == c->leb_size) {
			if (lprops->free != c->leb_size)
				c->lst.empty_lebs += 1;
		} else if (lprops->free == c->leb_size)
			c->lst.empty_lebs -= 1;
		lprops->free = free;
	}

	if (dirty != LPROPS_NC) {
		dirty = ALIGN(dirty, 8);
		c->lst.total_dirty += dirty - lprops->dirty;
		lprops->dirty = dirty;
	}

	if (flags != LPROPS_NC) {
		/* Take care about indexing LEBs counter if needed */
		if ((lprops->flags & LPROPS_INDEX)) {
			if (!(flags & LPROPS_INDEX))
				c->lst.idx_lebs -= 1;
		} else if (flags & LPROPS_INDEX)
			c->lst.idx_lebs += 1;
		lprops->flags = flags;
	}

	if (!(lprops->flags & LPROPS_INDEX)) {
		int new_spc;

		new_spc = lprops->free + lprops->dirty;
		if (new_spc < c->dead_wm)
			c->lst.total_dead += new_spc;
		else
			c->lst.total_dark += ubifs_calc_dark(c, new_spc);

		c->lst.total_used += c->leb_size - new_spc;
	}

	if ((lprops->flags & LPROPS_TAKEN) && lprops->free == c->leb_size)
		c->lst.taken_empty_lebs += 1;

	change_category(c, lprops);
	c->idx_gc_cnt += idx_gc_cnt;
	spin_unlock(&c->space_lock);
	return lprops;
}