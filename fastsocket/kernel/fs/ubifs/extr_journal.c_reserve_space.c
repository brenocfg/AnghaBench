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
struct ubifs_wbuf {int offs; int used; int lnum; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  dtype; int /*<<< orphan*/  jhead; } ;
struct ubifs_info {int leb_size; scalar_t__ ro_media; TYPE_1__* jheads; } ;
struct TYPE_2__ {struct ubifs_wbuf wbuf; } ;

/* Variables and functions */
 int BASEHD ; 
 int EAGAIN ; 
 int ENOSPC ; 
 int EROFS ; 
 int /*<<< orphan*/  dbg_jhead (int) ; 
 int /*<<< orphan*/  dbg_jnl (char*,...) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_add_bud_to_log (struct ubifs_info*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int ubifs_find_free_space (struct ubifs_info*,int,int*,int) ; 
 int ubifs_garbage_collect (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_return_leb (struct ubifs_info*,int) ; 
 int ubifs_wbuf_seek_nolock (struct ubifs_wbuf*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reserve_space(struct ubifs_info *c, int jhead, int len)
{
	int err = 0, err1, retries = 0, avail, lnum, offs, squeeze;
	struct ubifs_wbuf *wbuf = &c->jheads[jhead].wbuf;

	/*
	 * Typically, the base head has smaller nodes written to it, so it is
	 * better to try to allocate space at the ends of eraseblocks. This is
	 * what the squeeze parameter does.
	 */
	squeeze = (jhead == BASEHD);
again:
	mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);

	if (c->ro_media) {
		err = -EROFS;
		goto out_unlock;
	}

	avail = c->leb_size - wbuf->offs - wbuf->used;
	if (wbuf->lnum != -1 && avail >= len)
		return 0;

	/*
	 * Write buffer wasn't seek'ed or there is no enough space - look for an
	 * LEB with some empty space.
	 */
	lnum = ubifs_find_free_space(c, len, &offs, squeeze);
	if (lnum >= 0) {
		/* Found an LEB, add it to the journal head */
		err = ubifs_add_bud_to_log(c, jhead, lnum, offs);
		if (err)
			goto out_return;
		/* A new bud was successfully allocated and added to the log */
		goto out;
	}

	err = lnum;
	if (err != -ENOSPC)
		goto out_unlock;

	/*
	 * No free space, we have to run garbage collector to make
	 * some. But the write-buffer mutex has to be unlocked because
	 * GC also takes it.
	 */
	dbg_jnl("no free space in jhead %s, run GC", dbg_jhead(jhead));
	mutex_unlock(&wbuf->io_mutex);

	lnum = ubifs_garbage_collect(c, 0);
	if (lnum < 0) {
		err = lnum;
		if (err != -ENOSPC)
			return err;

		/*
		 * GC could not make a free LEB. But someone else may
		 * have allocated new bud for this journal head,
		 * because we dropped @wbuf->io_mutex, so try once
		 * again.
		 */
		dbg_jnl("GC couldn't make a free LEB for jhead %s",
			dbg_jhead(jhead));
		if (retries++ < 2) {
			dbg_jnl("retry (%d)", retries);
			goto again;
		}

		dbg_jnl("return -ENOSPC");
		return err;
	}

	mutex_lock_nested(&wbuf->io_mutex, wbuf->jhead);
	dbg_jnl("got LEB %d for jhead %s", lnum, dbg_jhead(jhead));
	avail = c->leb_size - wbuf->offs - wbuf->used;

	if (wbuf->lnum != -1 && avail >= len) {
		/*
		 * Someone else has switched the journal head and we have
		 * enough space now. This happens when more than one process is
		 * trying to write to the same journal head at the same time.
		 */
		dbg_jnl("return LEB %d back, already have LEB %d:%d",
			lnum, wbuf->lnum, wbuf->offs + wbuf->used);
		err = ubifs_return_leb(c, lnum);
		if (err)
			goto out_unlock;
		return 0;
	}

	err = ubifs_add_bud_to_log(c, jhead, lnum, 0);
	if (err)
		goto out_return;
	offs = 0;

out:
	err = ubifs_wbuf_seek_nolock(wbuf, lnum, offs, wbuf->dtype);
	if (err)
		goto out_unlock;

	return 0;

out_unlock:
	mutex_unlock(&wbuf->io_mutex);
	return err;

out_return:
	/* An error occurred and the LEB has to be returned to lprops */
	ubifs_assert(err < 0);
	err1 = ubifs_return_leb(c, lnum);
	if (err1 && err == -EAGAIN)
		/*
		 * Return original error code only if it is not %-EAGAIN,
		 * which is not really an error. Otherwise, return the error
		 * code of 'ubifs_return_leb()'.
		 */
		err = err1;
	mutex_unlock(&wbuf->io_mutex);
	return err;
}