#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int (* ubifs_lpt_scan_callback ) (struct ubifs_info*,struct ubifs_lprops*,int,void*) ;
struct ubifs_pnode {size_t iip; TYPE_2__* nbranch; struct ubifs_pnode* parent; struct ubifs_lprops* lprops; } ;
struct ubifs_nnode {size_t iip; TYPE_2__* nbranch; struct ubifs_nnode* parent; struct ubifs_lprops* lprops; } ;
struct ubifs_lprops {int lnum; } ;
struct ubifs_info {int leb_cnt; int main_first; int lpt_hght; int pnodes_have; struct ubifs_pnode* nroot; } ;
struct ubifs_cnode {int dummy; } ;
struct TYPE_6__ {struct ubifs_pnode* nnode; struct ubifs_pnode* pnode; } ;
struct TYPE_4__ {struct ubifs_pnode* parent; } ;
struct lpt_scan_node {int in_tree; TYPE_3__ ptr; int /*<<< orphan*/  pnode; TYPE_1__ cnode; int /*<<< orphan*/  nnode; } ;
struct TYPE_5__ {struct ubifs_pnode* pnode; struct ubifs_pnode* nnode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct ubifs_pnode*) ; 
 int LPT_SCAN_ADD ; 
 int LPT_SCAN_STOP ; 
 int PTR_ERR (struct ubifs_pnode*) ; 
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 
 int dbg_check_cats (struct ubifs_info*) ; 
 int dbg_check_lpt_nodes (struct ubifs_info*,struct ubifs_cnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lpt_scan_node*) ; 
 void* kmalloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ubifs_pnode*,int /*<<< orphan*/ *,size_t const) ; 
 struct ubifs_pnode* scan_get_nnode (struct ubifs_info*,struct lpt_scan_node*,struct ubifs_pnode*,int) ; 
 struct ubifs_pnode* scan_get_pnode (struct ubifs_info*,struct lpt_scan_node*,struct ubifs_pnode*,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_ensure_cat (struct ubifs_info*,struct ubifs_lprops*) ; 
 int ubifs_read_nnode (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cats (struct ubifs_info*,struct ubifs_pnode*) ; 

int ubifs_lpt_scan_nolock(struct ubifs_info *c, int start_lnum, int end_lnum,
			  ubifs_lpt_scan_callback scan_cb, void *data)
{
	int err = 0, i, h, iip, shft;
	struct ubifs_nnode *nnode;
	struct ubifs_pnode *pnode;
	struct lpt_scan_node *path;

	if (start_lnum == -1) {
		start_lnum = end_lnum + 1;
		if (start_lnum >= c->leb_cnt)
			start_lnum = c->main_first;
	}

	ubifs_assert(start_lnum >= c->main_first && start_lnum < c->leb_cnt);
	ubifs_assert(end_lnum >= c->main_first && end_lnum < c->leb_cnt);

	if (!c->nroot) {
		err = ubifs_read_nnode(c, NULL, 0);
		if (err)
			return err;
	}

	path = kmalloc(sizeof(struct lpt_scan_node) * (c->lpt_hght + 1),
		       GFP_NOFS);
	if (!path)
		return -ENOMEM;

	path[0].ptr.nnode = c->nroot;
	path[0].in_tree = 1;
again:
	/* Descend to the pnode containing start_lnum */
	nnode = c->nroot;
	i = start_lnum - c->main_first;
	shft = c->lpt_hght * UBIFS_LPT_FANOUT_SHIFT;
	for (h = 1; h < c->lpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
		shft -= UBIFS_LPT_FANOUT_SHIFT;
		nnode = scan_get_nnode(c, path + h, nnode, iip);
		if (IS_ERR(nnode)) {
			err = PTR_ERR(nnode);
			goto out;
		}
	}
	iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
	shft -= UBIFS_LPT_FANOUT_SHIFT;
	pnode = scan_get_pnode(c, path + h, nnode, iip);
	if (IS_ERR(pnode)) {
		err = PTR_ERR(pnode);
		goto out;
	}
	iip = (i & (UBIFS_LPT_FANOUT - 1));

	/* Loop for each lprops */
	while (1) {
		struct ubifs_lprops *lprops = &pnode->lprops[iip];
		int ret, lnum = lprops->lnum;

		ret = scan_cb(c, lprops, path[h].in_tree, data);
		if (ret < 0) {
			err = ret;
			goto out;
		}
		if (ret & LPT_SCAN_ADD) {
			/* Add all the nodes in path to the tree in memory */
			for (h = 1; h < c->lpt_hght; h++) {
				const size_t sz = sizeof(struct ubifs_nnode);
				struct ubifs_nnode *parent;

				if (path[h].in_tree)
					continue;
				nnode = kmalloc(sz, GFP_NOFS);
				if (!nnode) {
					err = -ENOMEM;
					goto out;
				}
				memcpy(nnode, &path[h].nnode, sz);
				parent = nnode->parent;
				parent->nbranch[nnode->iip].nnode = nnode;
				path[h].ptr.nnode = nnode;
				path[h].in_tree = 1;
				path[h + 1].cnode.parent = nnode;
			}
			if (path[h].in_tree)
				ubifs_ensure_cat(c, lprops);
			else {
				const size_t sz = sizeof(struct ubifs_pnode);
				struct ubifs_nnode *parent;

				pnode = kmalloc(sz, GFP_NOFS);
				if (!pnode) {
					err = -ENOMEM;
					goto out;
				}
				memcpy(pnode, &path[h].pnode, sz);
				parent = pnode->parent;
				parent->nbranch[pnode->iip].pnode = pnode;
				path[h].ptr.pnode = pnode;
				path[h].in_tree = 1;
				update_cats(c, pnode);
				c->pnodes_have += 1;
			}
			err = dbg_check_lpt_nodes(c, (struct ubifs_cnode *)
						  c->nroot, 0, 0);
			if (err)
				goto out;
			err = dbg_check_cats(c);
			if (err)
				goto out;
		}
		if (ret & LPT_SCAN_STOP) {
			err = 0;
			break;
		}
		/* Get the next lprops */
		if (lnum == end_lnum) {
			/*
			 * We got to the end without finding what we were
			 * looking for
			 */
			err = -ENOSPC;
			goto out;
		}
		if (lnum + 1 >= c->leb_cnt) {
			/* Wrap-around to the beginning */
			start_lnum = c->main_first;
			goto again;
		}
		if (iip + 1 < UBIFS_LPT_FANOUT) {
			/* Next lprops is in the same pnode */
			iip += 1;
			continue;
		}
		/* We need to get the next pnode. Go up until we can go right */
		iip = pnode->iip;
		while (1) {
			h -= 1;
			ubifs_assert(h >= 0);
			nnode = path[h].ptr.nnode;
			if (iip + 1 < UBIFS_LPT_FANOUT)
				break;
			iip = nnode->iip;
		}
		/* Go right */
		iip += 1;
		/* Descend to the pnode */
		h += 1;
		for (; h < c->lpt_hght; h++) {
			nnode = scan_get_nnode(c, path + h, nnode, iip);
			if (IS_ERR(nnode)) {
				err = PTR_ERR(nnode);
				goto out;
			}
			iip = 0;
		}
		pnode = scan_get_pnode(c, path + h, nnode, iip);
		if (IS_ERR(pnode)) {
			err = PTR_ERR(pnode);
			goto out;
		}
		iip = 0;
	}
out:
	kfree(path);
	return err;
}