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
struct TYPE_2__ {int idx_lebs; } ;
struct ubifs_info {int* gap_lebs; int ileb_cnt; int /*<<< orphan*/  space_lock; TYPE_1__ lst; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dbg_dump_budg (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_dump_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_force_in_the_gaps_enabled ; 
 int /*<<< orphan*/  dbg_gc (char*,int,...) ; 
 int get_leb_cnt (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int layout_leb_in_gaps (struct ubifs_info*,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 

__attribute__((used)) static int layout_in_gaps(struct ubifs_info *c, int cnt)
{
	int err, leb_needed_cnt, written, *p;

	dbg_gc("%d znodes to write", cnt);

	c->gap_lebs = kmalloc(sizeof(int) * (c->lst.idx_lebs + 1), GFP_NOFS);
	if (!c->gap_lebs)
		return -ENOMEM;

	p = c->gap_lebs;
	do {
		ubifs_assert(p < c->gap_lebs + sizeof(int) * c->lst.idx_lebs);
		written = layout_leb_in_gaps(c, p);
		if (written < 0) {
			err = written;
			if (err != -ENOSPC) {
				kfree(c->gap_lebs);
				c->gap_lebs = NULL;
				return err;
			}
			if (!dbg_force_in_the_gaps_enabled) {
				/*
				 * Do not print scary warnings if the debugging
				 * option which forces in-the-gaps is enabled.
				 */
				ubifs_err("out of space");
				spin_lock(&c->space_lock);
				dbg_dump_budg(c);
				spin_unlock(&c->space_lock);
				dbg_dump_lprops(c);
			}
			/* Try to commit anyway */
			err = 0;
			break;
		}
		p++;
		cnt -= written;
		leb_needed_cnt = get_leb_cnt(c, cnt);
		dbg_gc("%d znodes remaining, need %d LEBs, have %d", cnt,
		       leb_needed_cnt, c->ileb_cnt);
	} while (leb_needed_cnt > c->ileb_cnt);

	*p = -1;
	return 0;
}