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
struct ubifs_info {int nhead_lnum; int nhead_offs; int lsave_sz; int leb_size; int lsave_lnum; int lsave_offs; int ltab_sz; int ltab_lnum; int ltab_offs; int nnode_sz; int dirty_nn_cnt; int pnode_sz; int dirty_pn_cnt; int lpt_first; int lpt_last; int lpt_lnum; int lpt_offs; int /*<<< orphan*/  min_io_size; struct ubifs_cnode* lpt_cnext; int /*<<< orphan*/  big_lpt; } ;
struct ubifs_cnode {size_t iip; struct ubifs_cnode* cnext; TYPE_2__* parent; scalar_t__ level; } ;
struct TYPE_4__ {TYPE_1__* nbranch; } ;
struct TYPE_3__ {int lnum; int offs; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int alloc_lpt_leb (struct ubifs_info*,int*) ; 
 int dbg_chk_lpt_sz (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  dbg_dump_lpt_info (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_dump_lpt_lebs (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_err (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 int /*<<< orphan*/  upd_ltab (struct ubifs_info*,int,int,int) ; 

__attribute__((used)) static int layout_cnodes(struct ubifs_info *c)
{
	int lnum, offs, len, alen, done_lsave, done_ltab, err;
	struct ubifs_cnode *cnode;

	err = dbg_chk_lpt_sz(c, 0, 0);
	if (err)
		return err;
	cnode = c->lpt_cnext;
	if (!cnode)
		return 0;
	lnum = c->nhead_lnum;
	offs = c->nhead_offs;
	/* Try to place lsave and ltab nicely */
	done_lsave = !c->big_lpt;
	done_ltab = 0;
	if (!done_lsave && offs + c->lsave_sz <= c->leb_size) {
		done_lsave = 1;
		c->lsave_lnum = lnum;
		c->lsave_offs = offs;
		offs += c->lsave_sz;
		dbg_chk_lpt_sz(c, 1, c->lsave_sz);
	}

	if (offs + c->ltab_sz <= c->leb_size) {
		done_ltab = 1;
		c->ltab_lnum = lnum;
		c->ltab_offs = offs;
		offs += c->ltab_sz;
		dbg_chk_lpt_sz(c, 1, c->ltab_sz);
	}

	do {
		if (cnode->level) {
			len = c->nnode_sz;
			c->dirty_nn_cnt -= 1;
		} else {
			len = c->pnode_sz;
			c->dirty_pn_cnt -= 1;
		}
		while (offs + len > c->leb_size) {
			alen = ALIGN(offs, c->min_io_size);
			upd_ltab(c, lnum, c->leb_size - alen, alen - offs);
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = alloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
			/* Try to place lsave and ltab nicely */
			if (!done_lsave) {
				done_lsave = 1;
				c->lsave_lnum = lnum;
				c->lsave_offs = offs;
				offs += c->lsave_sz;
				dbg_chk_lpt_sz(c, 1, c->lsave_sz);
				continue;
			}
			if (!done_ltab) {
				done_ltab = 1;
				c->ltab_lnum = lnum;
				c->ltab_offs = offs;
				offs += c->ltab_sz;
				dbg_chk_lpt_sz(c, 1, c->ltab_sz);
				continue;
			}
			break;
		}
		if (cnode->parent) {
			cnode->parent->nbranch[cnode->iip].lnum = lnum;
			cnode->parent->nbranch[cnode->iip].offs = offs;
		} else {
			c->lpt_lnum = lnum;
			c->lpt_offs = offs;
		}
		offs += len;
		dbg_chk_lpt_sz(c, 1, len);
		cnode = cnode->cnext;
	} while (cnode && cnode != c->lpt_cnext);

	/* Make sure to place LPT's save table */
	if (!done_lsave) {
		if (offs + c->lsave_sz > c->leb_size) {
			alen = ALIGN(offs, c->min_io_size);
			upd_ltab(c, lnum, c->leb_size - alen, alen - offs);
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = alloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
		}
		done_lsave = 1;
		c->lsave_lnum = lnum;
		c->lsave_offs = offs;
		offs += c->lsave_sz;
		dbg_chk_lpt_sz(c, 1, c->lsave_sz);
	}

	/* Make sure to place LPT's own lprops table */
	if (!done_ltab) {
		if (offs + c->ltab_sz > c->leb_size) {
			alen = ALIGN(offs, c->min_io_size);
			upd_ltab(c, lnum, c->leb_size - alen, alen - offs);
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = alloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
		}
		done_ltab = 1;
		c->ltab_lnum = lnum;
		c->ltab_offs = offs;
		offs += c->ltab_sz;
		dbg_chk_lpt_sz(c, 1, c->ltab_sz);
	}

	alen = ALIGN(offs, c->min_io_size);
	upd_ltab(c, lnum, c->leb_size - alen, alen - offs);
	dbg_chk_lpt_sz(c, 4, alen - offs);
	err = dbg_chk_lpt_sz(c, 3, alen);
	if (err)
		return err;
	return 0;

no_space:
	ubifs_err("LPT out of space");
	dbg_err("LPT out of space at LEB %d:%d needing %d, done_ltab %d, "
		"done_lsave %d", lnum, offs, len, done_ltab, done_lsave);
	dbg_dump_lpt_info(c);
	dbg_dump_lpt_lebs(c);
	dump_stack();
	return err;
}