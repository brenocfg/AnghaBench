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
struct ubifs_lprops {int dirty; scalar_t__ free; int flags; } ;
struct ubifs_info {scalar_t__ leb_size; } ;
struct replay_entry {scalar_t__ offs; int dirty; int /*<<< orphan*/  free; int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_lprops const*) ; 
 int LPROPS_TAKEN ; 
 int PTR_ERR (struct ubifs_lprops const*) ; 
 int /*<<< orphan*/  dbg_gc (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dbg_mnt (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dbg_msg (char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 struct ubifs_lprops* ubifs_change_lp (struct ubifs_info*,struct ubifs_lprops const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_get_lprops (struct ubifs_info*) ; 
 struct ubifs_lprops* ubifs_lpt_lookup_dirty (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_release_lprops (struct ubifs_info*) ; 

__attribute__((used)) static int set_bud_lprops(struct ubifs_info *c, struct replay_entry *r)
{
	const struct ubifs_lprops *lp;
	int err = 0, dirty;

	ubifs_get_lprops(c);

	lp = ubifs_lpt_lookup_dirty(c, r->lnum);
	if (IS_ERR(lp)) {
		err = PTR_ERR(lp);
		goto out;
	}

	dirty = lp->dirty;
	if (r->offs == 0 && (lp->free != c->leb_size || lp->dirty != 0)) {
		/*
		 * The LEB was added to the journal with a starting offset of
		 * zero which means the LEB must have been empty. The LEB
		 * property values should be lp->free == c->leb_size and
		 * lp->dirty == 0, but that is not the case. The reason is that
		 * the LEB was garbage collected. The garbage collector resets
		 * the free and dirty space without recording it anywhere except
		 * lprops, so if there is not a commit then lprops does not have
		 * that information next time the file system is mounted.
		 *
		 * We do not need to adjust free space because the scan has told
		 * us the exact value which is recorded in the replay entry as
		 * r->free.
		 *
		 * However we do need to subtract from the dirty space the
		 * amount of space that the garbage collector reclaimed, which
		 * is the whole LEB minus the amount of space that was free.
		 */
		dbg_mnt("bud LEB %d was GC'd (%d free, %d dirty)", r->lnum,
			lp->free, lp->dirty);
		dbg_gc("bud LEB %d was GC'd (%d free, %d dirty)", r->lnum,
			lp->free, lp->dirty);
		dirty -= c->leb_size - lp->free;
		/*
		 * If the replay order was perfect the dirty space would now be
		 * zero. The order is not perfect because the journal heads
		 * race with each other. This is not a problem but is does mean
		 * that the dirty space may temporarily exceed c->leb_size
		 * during the replay.
		 */
		if (dirty != 0)
			dbg_msg("LEB %d lp: %d free %d dirty "
				"replay: %d free %d dirty", r->lnum, lp->free,
				lp->dirty, r->free, r->dirty);
	}
	lp = ubifs_change_lp(c, lp, r->free, dirty + r->dirty,
			     lp->flags | LPROPS_TAKEN, 0);
	if (IS_ERR(lp)) {
		err = PTR_ERR(lp);
		goto out;
	}
out:
	ubifs_release_lprops(c);
	return err;
}