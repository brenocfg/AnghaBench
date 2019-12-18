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
struct ubifs_znode {int child_cnt; int level; int lnum; int offs; int len; int /*<<< orphan*/  flags; struct ubifs_znode* cnext; struct ubifs_zbranch* zbranch; } ;
struct ubifs_zbranch {struct ubifs_znode* znode; int /*<<< orphan*/  len; int /*<<< orphan*/  lnum; int /*<<< orphan*/  offs; int /*<<< orphan*/  key; } ;
struct ubifs_info {int ihead_lnum; int ihead_offs; int max_idx_node_sz; int min_io_size; int leb_size; int* ilebs; TYPE_1__* dbg; struct ubifs_idx_node* cbuf; struct ubifs_znode* cnext; struct ubifs_znode* enext; } ;
struct TYPE_4__ {int /*<<< orphan*/  node_type; } ;
struct ubifs_idx_node {void* level; void* child_cnt; TYPE_2__ ch; } ;
struct ubifs_branch {void* len; void* offs; void* lnum; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int new_ihead_lnum; int new_ihead_offs; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_ZNODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  LPROPS_NC ; 
 int /*<<< orphan*/  LPROPS_TAKEN ; 
 int /*<<< orphan*/  UBIFS_IDX_NODE ; 
 int /*<<< orphan*/  UBI_SHORTTERM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  key_write_idx (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (struct ubifs_idx_node*,struct ubifs_idx_node*,int) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 struct ubifs_branch* ubifs_idx_branch (struct ubifs_info*,struct ubifs_idx_node*,int) ; 
 int ubifs_idx_node_sz (struct ubifs_info*,int) ; 
 int ubifs_leb_write (struct ubifs_info*,int,struct ubifs_idx_node*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_pad (struct ubifs_info*,struct ubifs_idx_node*,int) ; 
 int /*<<< orphan*/  ubifs_prepare_node (struct ubifs_info*,struct ubifs_idx_node*,int,int /*<<< orphan*/ ) ; 
 int ubifs_update_one_lp (struct ubifs_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

__attribute__((used)) static int write_index(struct ubifs_info *c)
{
	struct ubifs_idx_node *idx;
	struct ubifs_znode *znode, *cnext;
	int i, lnum, offs, len, next_len, buf_len, buf_offs, used;
	int avail, wlen, err, lnum_pos = 0;

	cnext = c->enext;
	if (!cnext)
		return 0;

	/*
	 * Always write index nodes to the index head so that index nodes and
	 * other types of nodes are never mixed in the same erase block.
	 */
	lnum = c->ihead_lnum;
	buf_offs = c->ihead_offs;

	/* Allocate commit buffer */
	buf_len = ALIGN(c->max_idx_node_sz, c->min_io_size);
	used = 0;
	avail = buf_len;

	/* Ensure there is enough room for first write */
	next_len = ubifs_idx_node_sz(c, cnext->child_cnt);
	if (buf_offs + next_len > c->leb_size) {
		err = ubifs_update_one_lp(c, lnum, LPROPS_NC, 0, 0,
					  LPROPS_TAKEN);
		if (err)
			return err;
		lnum = -1;
	}

	while (1) {
		cond_resched();

		znode = cnext;
		idx = c->cbuf + used;

		/* Make index node */
		idx->ch.node_type = UBIFS_IDX_NODE;
		idx->child_cnt = cpu_to_le16(znode->child_cnt);
		idx->level = cpu_to_le16(znode->level);
		for (i = 0; i < znode->child_cnt; i++) {
			struct ubifs_branch *br = ubifs_idx_branch(c, idx, i);
			struct ubifs_zbranch *zbr = &znode->zbranch[i];

			key_write_idx(c, &zbr->key, &br->key);
			br->lnum = cpu_to_le32(zbr->lnum);
			br->offs = cpu_to_le32(zbr->offs);
			br->len = cpu_to_le32(zbr->len);
			if (!zbr->lnum || !zbr->len) {
				ubifs_err("bad ref in znode");
				dbg_dump_znode(c, znode);
				if (zbr->znode)
					dbg_dump_znode(c, zbr->znode);
			}
		}
		len = ubifs_idx_node_sz(c, znode->child_cnt);
		ubifs_prepare_node(c, idx, len, 0);

		/* Determine the index node position */
		if (lnum == -1) {
			lnum = c->ilebs[lnum_pos++];
			buf_offs = 0;
			used = 0;
			avail = buf_len;
		}
		offs = buf_offs + used;

#ifdef CONFIG_UBIFS_FS_DEBUG
		if (lnum != znode->lnum || offs != znode->offs ||
		    len != znode->len) {
			ubifs_err("inconsistent znode posn");
			return -EINVAL;
		}
#endif

		/* Grab some stuff from znode while we still can */
		cnext = znode->cnext;

		ubifs_assert(ubifs_zn_dirty(znode));
		ubifs_assert(test_bit(COW_ZNODE, &znode->flags));

		/*
		 * It is important that other threads should see %DIRTY_ZNODE
		 * flag cleared before %COW_ZNODE. Specifically, it matters in
		 * the 'dirty_cow_znode()' function. This is the reason for the
		 * first barrier. Also, we want the bit changes to be seen to
		 * other threads ASAP, to avoid unnecesarry copying, which is
		 * the reason for the second barrier.
		 */
		clear_bit(DIRTY_ZNODE, &znode->flags);
		smp_mb__before_clear_bit();
		clear_bit(COW_ZNODE, &znode->flags);
		smp_mb__after_clear_bit();

		/* Do not access znode from this point on */

		/* Update buffer positions */
		wlen = used + len;
		used += ALIGN(len, 8);
		avail -= ALIGN(len, 8);

		/*
		 * Calculate the next index node length to see if there is
		 * enough room for it
		 */
		if (cnext == c->cnext)
			next_len = 0;
		else
			next_len = ubifs_idx_node_sz(c, cnext->child_cnt);

		if (c->min_io_size == 1) {
			/*
			 * Write the prepared index node immediately if there is
			 * no minimum IO size
			 */
			err = ubifs_leb_write(c, lnum, c->cbuf, buf_offs,
					      wlen, UBI_SHORTTERM);
			if (err)
				return err;
			buf_offs += ALIGN(wlen, 8);
			if (next_len) {
				used = 0;
				avail = buf_len;
				if (buf_offs + next_len > c->leb_size) {
					err = ubifs_update_one_lp(c, lnum,
						LPROPS_NC, 0, 0, LPROPS_TAKEN);
					if (err)
						return err;
					lnum = -1;
				}
				continue;
			}
		} else {
			int blen, nxt_offs = buf_offs + used + next_len;

			if (next_len && nxt_offs <= c->leb_size) {
				if (avail > 0)
					continue;
				else
					blen = buf_len;
			} else {
				wlen = ALIGN(wlen, 8);
				blen = ALIGN(wlen, c->min_io_size);
				ubifs_pad(c, c->cbuf + wlen, blen - wlen);
			}
			/*
			 * The buffer is full or there are no more znodes
			 * to do
			 */
			err = ubifs_leb_write(c, lnum, c->cbuf, buf_offs,
					      blen, UBI_SHORTTERM);
			if (err)
				return err;
			buf_offs += blen;
			if (next_len) {
				if (nxt_offs > c->leb_size) {
					err = ubifs_update_one_lp(c, lnum,
						LPROPS_NC, 0, 0, LPROPS_TAKEN);
					if (err)
						return err;
					lnum = -1;
				}
				used -= blen;
				if (used < 0)
					used = 0;
				avail = buf_len - used;
				memmove(c->cbuf, c->cbuf + blen, used);
				continue;
			}
		}
		break;
	}

#ifdef CONFIG_UBIFS_FS_DEBUG
	if (lnum != c->dbg->new_ihead_lnum ||
	    buf_offs != c->dbg->new_ihead_offs) {
		ubifs_err("inconsistent ihead");
		return -EINVAL;
	}
#endif

	c->ihead_lnum = lnum;
	c->ihead_offs = buf_offs;

	return 0;
}