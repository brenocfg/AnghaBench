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
struct ubifs_pnode {int dummy; } ;
struct ubifs_nnode {int dummy; } ;
struct ubifs_info {int nhead_lnum; int nhead_offs; int lsave_sz; int leb_size; int ltab_sz; int nnode_sz; int pnode_sz; int lpt_first; int lpt_last; int lpt_lnum; int lpt_offs; int ltab_lnum; int ltab_offs; int lsave_lnum; int lsave_offs; scalar_t__ big_lpt; int /*<<< orphan*/  min_io_size; int /*<<< orphan*/  ltab_cmt; int /*<<< orphan*/  lsave; struct ubifs_cnode* lpt_cnext; void* lpt_buf; } ;
struct ubifs_cnode {struct ubifs_cnode* cnext; int /*<<< orphan*/  flags; scalar_t__ level; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_CNODE ; 
 int /*<<< orphan*/  UBI_SHORTTERM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dbg_chk_lpt_sz (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  dbg_dump_lpt_info (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_dump_lpt_lebs (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_err (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dbg_lp (char*,int,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int realloc_lpt_leb (struct ubifs_info*,int*) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int ubifs_leb_write (struct ubifs_info*,int,void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_pack_lsave (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_pack_ltab (struct ubifs_info*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_pack_nnode (struct ubifs_info*,void*,struct ubifs_nnode*) ; 
 int /*<<< orphan*/  ubifs_pack_pnode (struct ubifs_info*,void*,struct ubifs_pnode*) ; 

__attribute__((used)) static int write_cnodes(struct ubifs_info *c)
{
	int lnum, offs, len, from, err, wlen, alen, done_ltab, done_lsave;
	struct ubifs_cnode *cnode;
	void *buf = c->lpt_buf;

	cnode = c->lpt_cnext;
	if (!cnode)
		return 0;
	lnum = c->nhead_lnum;
	offs = c->nhead_offs;
	from = offs;
	/* Ensure empty LEB is unmapped */
	if (offs == 0) {
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
	}
	/* Try to place lsave and ltab nicely */
	done_lsave = !c->big_lpt;
	done_ltab = 0;
	if (!done_lsave && offs + c->lsave_sz <= c->leb_size) {
		done_lsave = 1;
		ubifs_pack_lsave(c, buf + offs, c->lsave);
		offs += c->lsave_sz;
		dbg_chk_lpt_sz(c, 1, c->lsave_sz);
	}

	if (offs + c->ltab_sz <= c->leb_size) {
		done_ltab = 1;
		ubifs_pack_ltab(c, buf + offs, c->ltab_cmt);
		offs += c->ltab_sz;
		dbg_chk_lpt_sz(c, 1, c->ltab_sz);
	}

	/* Loop for each cnode */
	do {
		if (cnode->level)
			len = c->nnode_sz;
		else
			len = c->pnode_sz;
		while (offs + len > c->leb_size) {
			wlen = offs - from;
			if (wlen) {
				alen = ALIGN(wlen, c->min_io_size);
				memset(buf + offs, 0xff, alen - wlen);
				err = ubifs_leb_write(c, lnum, buf + from, from,
						       alen, UBI_SHORTTERM);
				if (err)
					return err;
			}
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = realloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = from = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
			err = ubifs_leb_unmap(c, lnum);
			if (err)
				return err;
			/* Try to place lsave and ltab nicely */
			if (!done_lsave) {
				done_lsave = 1;
				ubifs_pack_lsave(c, buf + offs, c->lsave);
				offs += c->lsave_sz;
				dbg_chk_lpt_sz(c, 1, c->lsave_sz);
				continue;
			}
			if (!done_ltab) {
				done_ltab = 1;
				ubifs_pack_ltab(c, buf + offs, c->ltab_cmt);
				offs += c->ltab_sz;
				dbg_chk_lpt_sz(c, 1, c->ltab_sz);
				continue;
			}
			break;
		}
		if (cnode->level)
			ubifs_pack_nnode(c, buf + offs,
					 (struct ubifs_nnode *)cnode);
		else
			ubifs_pack_pnode(c, buf + offs,
					 (struct ubifs_pnode *)cnode);
		/*
		 * The reason for the barriers is the same as in case of TNC.
		 * See comment in 'write_index()'. 'dirty_cow_nnode()' and
		 * 'dirty_cow_pnode()' are the functions for which this is
		 * important.
		 */
		clear_bit(DIRTY_CNODE, &cnode->flags);
		smp_mb__before_clear_bit();
		clear_bit(COW_ZNODE, &cnode->flags);
		smp_mb__after_clear_bit();
		offs += len;
		dbg_chk_lpt_sz(c, 1, len);
		cnode = cnode->cnext;
	} while (cnode && cnode != c->lpt_cnext);

	/* Make sure to place LPT's save table */
	if (!done_lsave) {
		if (offs + c->lsave_sz > c->leb_size) {
			wlen = offs - from;
			alen = ALIGN(wlen, c->min_io_size);
			memset(buf + offs, 0xff, alen - wlen);
			err = ubifs_leb_write(c, lnum, buf + from, from, alen,
					      UBI_SHORTTERM);
			if (err)
				return err;
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = realloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = from = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
			err = ubifs_leb_unmap(c, lnum);
			if (err)
				return err;
		}
		done_lsave = 1;
		ubifs_pack_lsave(c, buf + offs, c->lsave);
		offs += c->lsave_sz;
		dbg_chk_lpt_sz(c, 1, c->lsave_sz);
	}

	/* Make sure to place LPT's own lprops table */
	if (!done_ltab) {
		if (offs + c->ltab_sz > c->leb_size) {
			wlen = offs - from;
			alen = ALIGN(wlen, c->min_io_size);
			memset(buf + offs, 0xff, alen - wlen);
			err = ubifs_leb_write(c, lnum, buf + from, from, alen,
					      UBI_SHORTTERM);
			if (err)
				return err;
			dbg_chk_lpt_sz(c, 2, c->leb_size - offs);
			err = realloc_lpt_leb(c, &lnum);
			if (err)
				goto no_space;
			offs = from = 0;
			ubifs_assert(lnum >= c->lpt_first &&
				     lnum <= c->lpt_last);
			err = ubifs_leb_unmap(c, lnum);
			if (err)
				return err;
		}
		done_ltab = 1;
		ubifs_pack_ltab(c, buf + offs, c->ltab_cmt);
		offs += c->ltab_sz;
		dbg_chk_lpt_sz(c, 1, c->ltab_sz);
	}

	/* Write remaining data in buffer */
	wlen = offs - from;
	alen = ALIGN(wlen, c->min_io_size);
	memset(buf + offs, 0xff, alen - wlen);
	err = ubifs_leb_write(c, lnum, buf + from, from, alen, UBI_SHORTTERM);
	if (err)
		return err;

	dbg_chk_lpt_sz(c, 4, alen - wlen);
	err = dbg_chk_lpt_sz(c, 3, ALIGN(offs, c->min_io_size));
	if (err)
		return err;

	c->nhead_lnum = lnum;
	c->nhead_offs = ALIGN(offs, c->min_io_size);

	dbg_lp("LPT root is at %d:%d", c->lpt_lnum, c->lpt_offs);
	dbg_lp("LPT head is at %d:%d", c->nhead_lnum, c->nhead_offs);
	dbg_lp("LPT ltab is at %d:%d", c->ltab_lnum, c->ltab_offs);
	if (c->big_lpt)
		dbg_lp("LPT lsave is at %d:%d", c->lsave_lnum, c->lsave_offs);

	return 0;

no_space:
	ubifs_err("LPT out of space mismatch");
	dbg_err("LPT out of space mismatch at LEB %d:%d needing %d, done_ltab "
		"%d, done_lsave %d", lnum, offs, len, done_ltab, done_lsave);
	dbg_dump_lpt_info(c);
	dbg_dump_lpt_lebs(c);
	dump_stack();
	return err;
}