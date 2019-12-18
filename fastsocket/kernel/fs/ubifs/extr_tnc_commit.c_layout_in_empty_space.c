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
struct ubifs_znode {int lnum; int offs; int len; int iip; int /*<<< orphan*/  child_cnt; struct ubifs_znode* cnext; struct ubifs_zbranch* zbranch; struct ubifs_znode* parent; } ;
struct ubifs_zbranch {int lnum; int offs; int len; } ;
struct TYPE_3__ {int lnum; int offs; int len; } ;
struct ubifs_info {int ihead_lnum; int ihead_offs; int min_io_size; int leb_size; scalar_t__ ileb_nxt; scalar_t__ ileb_cnt; int* ilebs; int calc_idx_sz; TYPE_2__* dbg; struct ubifs_znode* cnext; int /*<<< orphan*/  dirty_zn_cnt; TYPE_1__ zroot; int /*<<< orphan*/  fanout; struct ubifs_znode* enext; } ;
struct TYPE_4__ {int new_ihead_lnum; int new_ihead_offs; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 int ubifs_idx_node_sz (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int ubifs_update_one_lp (struct ubifs_info*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int layout_in_empty_space(struct ubifs_info *c)
{
	struct ubifs_znode *znode, *cnext, *zp;
	int lnum, offs, len, next_len, buf_len, buf_offs, used, avail;
	int wlen, blen, err;

	cnext = c->enext;
	if (!cnext)
		return 0;

	lnum = c->ihead_lnum;
	buf_offs = c->ihead_offs;

	buf_len = ubifs_idx_node_sz(c, c->fanout);
	buf_len = ALIGN(buf_len, c->min_io_size);
	used = 0;
	avail = buf_len;

	/* Ensure there is enough room for first write */
	next_len = ubifs_idx_node_sz(c, cnext->child_cnt);
	if (buf_offs + next_len > c->leb_size)
		lnum = -1;

	while (1) {
		znode = cnext;

		len = ubifs_idx_node_sz(c, znode->child_cnt);

		/* Determine the index node position */
		if (lnum == -1) {
			if (c->ileb_nxt >= c->ileb_cnt) {
				ubifs_err("out of space");
				return -ENOSPC;
			}
			lnum = c->ilebs[c->ileb_nxt++];
			buf_offs = 0;
			used = 0;
			avail = buf_len;
		}

		offs = buf_offs + used;

#ifdef CONFIG_UBIFS_FS_DEBUG
		znode->lnum = lnum;
		znode->offs = offs;
		znode->len = len;
#endif

		/* Update the parent */
		zp = znode->parent;
		if (zp) {
			struct ubifs_zbranch *zbr;
			int i;

			i = znode->iip;
			zbr = &zp->zbranch[i];
			zbr->lnum = lnum;
			zbr->offs = offs;
			zbr->len = len;
		} else {
			c->zroot.lnum = lnum;
			c->zroot.offs = offs;
			c->zroot.len = len;
		}
		c->calc_idx_sz += ALIGN(len, 8);

		/*
		 * Once lprops is updated, we can decrease the dirty znode count
		 * but it is easier to just do it here.
		 */
		atomic_long_dec(&c->dirty_zn_cnt);

		/*
		 * Calculate the next index node length to see if there is
		 * enough room for it
		 */
		cnext = znode->cnext;
		if (cnext == c->cnext)
			next_len = 0;
		else
			next_len = ubifs_idx_node_sz(c, cnext->child_cnt);

		if (c->min_io_size == 1) {
			buf_offs += ALIGN(len, 8);
			if (next_len) {
				if (buf_offs + next_len <= c->leb_size)
					continue;
				err = ubifs_update_one_lp(c, lnum, 0,
						c->leb_size - buf_offs, 0, 0);
				if (err)
					return err;
				lnum = -1;
				continue;
			}
			err = ubifs_update_one_lp(c, lnum,
					c->leb_size - buf_offs, 0, 0, 0);
			if (err)
				return err;
			break;
		}

		/* Update buffer positions */
		wlen = used + len;
		used += ALIGN(len, 8);
		avail -= ALIGN(len, 8);

		if (next_len != 0 &&
		    buf_offs + used + next_len <= c->leb_size &&
		    avail > 0)
			continue;

		if (avail <= 0 && next_len &&
		    buf_offs + used + next_len <= c->leb_size)
			blen = buf_len;
		else
			blen = ALIGN(wlen, c->min_io_size);

		/* The buffer is full or there are no more znodes to do */
		buf_offs += blen;
		if (next_len) {
			if (buf_offs + next_len > c->leb_size) {
				err = ubifs_update_one_lp(c, lnum,
					c->leb_size - buf_offs, blen - used,
					0, 0);
				if (err)
					return err;
				lnum = -1;
			}
			used -= blen;
			if (used < 0)
				used = 0;
			avail = buf_len - used;
			continue;
		}
		err = ubifs_update_one_lp(c, lnum, c->leb_size - buf_offs,
					  blen - used, 0, 0);
		if (err)
			return err;
		break;
	}

#ifdef CONFIG_UBIFS_FS_DEBUG
	c->dbg->new_ihead_lnum = lnum;
	c->dbg->new_ihead_offs = buf_offs;
#endif

	return 0;
}