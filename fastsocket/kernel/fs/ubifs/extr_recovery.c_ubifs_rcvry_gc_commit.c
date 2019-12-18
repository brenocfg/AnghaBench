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
struct ubifs_wbuf {int lnum; scalar_t__ offs; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  jhead; } ;
struct ubifs_lprops {int flags; int lnum; scalar_t__ free; scalar_t__ dirty; } ;
struct ubifs_info {int gc_lnum; scalar_t__ leb_size; TYPE_1__* jheads; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOSPC ; 
 size_t GCHD ; 
 int LEB_RETAINED ; 
 int LPROPS_INDEX ; 
 scalar_t__ LPROPS_NC ; 
 int /*<<< orphan*/  dbg_err (char*,...) ; 
 int /*<<< orphan*/  dbg_rcvry (char*,...) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int ubifs_change_one_lp (struct ubifs_info*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ubifs_find_dirty_leb (struct ubifs_info*,struct ubifs_lprops*,scalar_t__,int) ; 
 int ubifs_find_free_leb_for_idx (struct ubifs_info*) ; 
 int ubifs_garbage_collect_leb (struct ubifs_info*,struct ubifs_lprops*) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int ubifs_return_leb (struct ubifs_info*,int) ; 
 int ubifs_run_commit (struct ubifs_info*) ; 
 int ubifs_wbuf_sync_nolock (struct ubifs_wbuf*) ; 

int ubifs_rcvry_gc_commit(struct ubifs_info *c)
{
	struct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;
	struct ubifs_lprops lp;
	int lnum, err;

	c->gc_lnum = -1;
	if (wbuf->lnum == -1) {
		dbg_rcvry("no GC head LEB");
		goto find_free;
	}
	/*
	 * See whether the used space in the dirtiest LEB fits in the GC head
	 * LEB.
	 */
	if (wbuf->offs == c->leb_size) {
		dbg_rcvry("no room in GC head LEB");
		goto find_free;
	}
	err = ubifs_find_dirty_leb(c, &lp, wbuf->offs, 2);
	if (err) {
		if (err == -ENOSPC)
			dbg_err("could not find a dirty LEB");
		return err;
	}
	ubifs_assert(!(lp.flags & LPROPS_INDEX));
	lnum = lp.lnum;
	if (lp.free + lp.dirty == c->leb_size) {
		/* An empty LEB was returned */
		if (lp.free != c->leb_size) {
			err = ubifs_change_one_lp(c, lnum, c->leb_size,
						  0, 0, 0, 0);
			if (err)
				return err;
		}
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
		c->gc_lnum = lnum;
		dbg_rcvry("allocated LEB %d for GC", lnum);
		/* Run the commit */
		dbg_rcvry("committing");
		return ubifs_run_commit(c);
	}
	/*
	 * There was no empty LEB so the used space in the dirtiest LEB must fit
	 * in the GC head LEB.
	 */
	if (lp.free + lp.dirty < wbuf->offs) {
		dbg_rcvry("LEB %d doesn't fit in GC head LEB %d:%d",
			  lnum, wbuf->lnum, wbuf->offs);
		err = ubifs_return_leb(c, lnum);
		if (err)
			return err;
		goto find_free;
	}
	/*
	 * We run the commit before garbage collection otherwise subsequent
	 * mounts will see the GC and orphan deletion in a different order.
	 */
	dbg_rcvry("committing");
	err = ubifs_run_commit(c);
	if (err)
		return err;
	/*
	 * The data in the dirtiest LEB fits in the GC head LEB, so do the GC
	 * - use locking to keep 'ubifs_assert()' happy.
	 */
	dbg_rcvry("GC'ing LEB %d", lnum);
	mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
	err = ubifs_garbage_collect_leb(c, &lp);
	if (err >= 0) {
		int err2 = ubifs_wbuf_sync_nolock(wbuf);

		if (err2)
			err = err2;
	}
	mutex_unlock(&wbuf->io_mutex);
	if (err < 0) {
		dbg_err("GC failed, error %d", err);
		if (err == -EAGAIN)
			err = -EINVAL;
		return err;
	}
	if (err != LEB_RETAINED) {
		dbg_err("GC returned %d", err);
		return -EINVAL;
	}
	err = ubifs_leb_unmap(c, c->gc_lnum);
	if (err)
		return err;
	dbg_rcvry("allocated LEB %d for GC", lnum);
	return 0;

find_free:
	/*
	 * There is no GC head LEB or the free space in the GC head LEB is too
	 * small. Allocate gc_lnum by calling 'ubifs_find_free_leb_for_idx()' so
	 * GC is not run.
	 */
	lnum = ubifs_find_free_leb_for_idx(c);
	if (lnum < 0) {
		dbg_err("could not find an empty LEB");
		return lnum;
	}
	/* And reset the index flag */
	err = ubifs_change_one_lp(c, lnum, LPROPS_NC, LPROPS_NC, 0,
				  LPROPS_INDEX, 0);
	if (err)
		return err;
	c->gc_lnum = lnum;
	dbg_rcvry("allocated LEB %d for GC", lnum);
	/* Run the commit */
	dbg_rcvry("committing");
	return ubifs_run_commit(c);
}