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
struct ubifs_pnode {int iip; struct ubifs_nnode* parent; void* num; struct ubifs_lprops* lprops; } ;
struct ubifs_nnode {struct ubifs_nbranch* nbranch; } ;
struct ubifs_nbranch {int lnum; int offs; struct ubifs_pnode* pnode; } ;
struct ubifs_lprops {int /*<<< orphan*/  flags; int /*<<< orphan*/  free; } ;
struct ubifs_info {int pnodes_have; scalar_t__ big_lpt; int /*<<< orphan*/  pnode_sz; int /*<<< orphan*/  ubi; int /*<<< orphan*/  leb_size; void* lpt_nod_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int UBIFS_LPT_FANOUT ; 
 void* calc_pnode_num_from_parent (struct ubifs_info*,struct ubifs_nnode*,int) ; 
 int /*<<< orphan*/  dbg_dump_pnode (struct ubifs_info*,struct ubifs_pnode*,struct ubifs_nnode*,int) ; 
 int /*<<< orphan*/  dbg_msg (char*,void*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_pnode*) ; 
 struct ubifs_pnode* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pnode_lnum (struct ubifs_info*,struct ubifs_pnode*) ; 
 int ubi_read (int /*<<< orphan*/ ,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_categorize_lprops (struct ubifs_info*,struct ubifs_lprops* const) ; 
 int /*<<< orphan*/  ubifs_err (char*,int,int,int) ; 
 int unpack_pnode (struct ubifs_info*,void*,struct ubifs_pnode*) ; 
 int validate_pnode (struct ubifs_info*,struct ubifs_pnode*,struct ubifs_nnode*,int) ; 

__attribute__((used)) static int read_pnode(struct ubifs_info *c, struct ubifs_nnode *parent, int iip)
{
	struct ubifs_nbranch *branch;
	struct ubifs_pnode *pnode = NULL;
	void *buf = c->lpt_nod_buf;
	int err, lnum, offs;

	branch = &parent->nbranch[iip];
	lnum = branch->lnum;
	offs = branch->offs;
	pnode = kzalloc(sizeof(struct ubifs_pnode), GFP_NOFS);
	if (!pnode) {
		err = -ENOMEM;
		goto out;
	}
	if (lnum == 0) {
		/*
		 * This pnode was not written which just means that the LEB
		 * properties in it describe empty LEBs. We make the pnode as
		 * though we had read it.
		 */
		int i;

		if (c->big_lpt)
			pnode->num = calc_pnode_num_from_parent(c, parent, iip);
		for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
			struct ubifs_lprops * const lprops = &pnode->lprops[i];

			lprops->free = c->leb_size;
			lprops->flags = ubifs_categorize_lprops(c, lprops);
		}
	} else {
		err = ubi_read(c->ubi, lnum, buf, offs, c->pnode_sz);
		if (err)
			goto out;
		err = unpack_pnode(c, buf, pnode);
		if (err)
			goto out;
	}
	err = validate_pnode(c, pnode, parent, iip);
	if (err)
		goto out;
	if (!c->big_lpt)
		pnode->num = calc_pnode_num_from_parent(c, parent, iip);
	branch->pnode = pnode;
	pnode->parent = parent;
	pnode->iip = iip;
	set_pnode_lnum(c, pnode);
	c->pnodes_have += 1;
	return 0;

out:
	ubifs_err("error %d reading pnode at %d:%d", err, lnum, offs);
	dbg_dump_pnode(c, pnode, parent, iip);
	dbg_msg("calc num: %d", calc_pnode_num_from_parent(c, parent, iip));
	kfree(pnode);
	return err;
}