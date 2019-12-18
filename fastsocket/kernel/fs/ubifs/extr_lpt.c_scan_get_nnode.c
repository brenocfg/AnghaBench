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
struct ubifs_nnode {int iip; struct ubifs_nnode* parent; scalar_t__ level; void* num; struct ubifs_nbranch* nbranch; } ;
struct ubifs_nbranch {scalar_t__ lnum; int /*<<< orphan*/  offs; struct ubifs_nnode* nnode; } ;
struct ubifs_info {scalar_t__ big_lpt; int /*<<< orphan*/  nnode_sz; int /*<<< orphan*/  ubi; void* lpt_nod_buf; } ;
struct TYPE_2__ {struct ubifs_nnode* nnode; } ;
struct lpt_scan_node {int in_tree; TYPE_1__ ptr; struct ubifs_nnode nnode; } ;

/* Variables and functions */
 struct ubifs_nnode* ERR_PTR (int) ; 
 void* calc_nnode_num_from_parent (struct ubifs_info*,struct ubifs_nnode*,int) ; 
 int /*<<< orphan*/  memset (struct ubifs_nnode*,int /*<<< orphan*/ ,int) ; 
 int ubi_read (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_unpack_nnode (struct ubifs_info*,void*,struct ubifs_nnode*) ; 
 int validate_nnode (struct ubifs_info*,struct ubifs_nnode*,struct ubifs_nnode*,int) ; 

__attribute__((used)) static struct ubifs_nnode *scan_get_nnode(struct ubifs_info *c,
					  struct lpt_scan_node *path,
					  struct ubifs_nnode *parent, int iip)
{
	struct ubifs_nbranch *branch;
	struct ubifs_nnode *nnode;
	void *buf = c->lpt_nod_buf;
	int err;

	branch = &parent->nbranch[iip];
	nnode = branch->nnode;
	if (nnode) {
		path->in_tree = 1;
		path->ptr.nnode = nnode;
		return nnode;
	}
	nnode = &path->nnode;
	path->in_tree = 0;
	path->ptr.nnode = nnode;
	memset(nnode, 0, sizeof(struct ubifs_nnode));
	if (branch->lnum == 0) {
		/*
		 * This nnode was not written which just means that the LEB
		 * properties in the subtree below it describe empty LEBs. We
		 * make the nnode as though we had read it, which in fact means
		 * doing almost nothing.
		 */
		if (c->big_lpt)
			nnode->num = calc_nnode_num_from_parent(c, parent, iip);
	} else {
		err = ubi_read(c->ubi, branch->lnum, buf, branch->offs,
			       c->nnode_sz);
		if (err)
			return ERR_PTR(err);
		err = ubifs_unpack_nnode(c, buf, nnode);
		if (err)
			return ERR_PTR(err);
	}
	err = validate_nnode(c, nnode, parent, iip);
	if (err)
		return ERR_PTR(err);
	if (!c->big_lpt)
		nnode->num = calc_nnode_num_from_parent(c, parent, iip);
	nnode->level = parent->level - 1;
	nnode->parent = parent;
	nnode->iip = iip;
	return nnode;
}