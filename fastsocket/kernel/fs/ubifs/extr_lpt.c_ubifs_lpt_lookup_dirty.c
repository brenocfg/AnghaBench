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
struct ubifs_pnode {struct ubifs_lprops* lprops; int /*<<< orphan*/  flags; } ;
struct ubifs_nnode {struct ubifs_lprops* lprops; int /*<<< orphan*/  flags; } ;
struct ubifs_lprops {int /*<<< orphan*/  flags; int /*<<< orphan*/  dirty; int /*<<< orphan*/  free; } ;
struct ubifs_info {int main_first; int lpt_hght; struct ubifs_pnode* nroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_CNODE ; 
 struct ubifs_lprops* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ubifs_pnode*) ; 
 int PTR_ERR (struct ubifs_pnode*) ; 
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 
 int /*<<< orphan*/  dbg_lp (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubifs_pnode* dirty_cow_nnode (struct ubifs_info*,struct ubifs_pnode*) ; 
 struct ubifs_pnode* dirty_cow_pnode (struct ubifs_info*,struct ubifs_pnode*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 struct ubifs_pnode* ubifs_get_nnode (struct ubifs_info*,struct ubifs_pnode*,int) ; 
 struct ubifs_pnode* ubifs_get_pnode (struct ubifs_info*,struct ubifs_pnode*,int) ; 
 int ubifs_read_nnode (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ubifs_lprops *ubifs_lpt_lookup_dirty(struct ubifs_info *c, int lnum)
{
	int err, i, h, iip, shft;
	struct ubifs_nnode *nnode;
	struct ubifs_pnode *pnode;

	if (!c->nroot) {
		err = ubifs_read_nnode(c, NULL, 0);
		if (err)
			return ERR_PTR(err);
	}
	nnode = c->nroot;
	nnode = dirty_cow_nnode(c, nnode);
	if (IS_ERR(nnode))
		return ERR_PTR(PTR_ERR(nnode));
	i = lnum - c->main_first;
	shft = c->lpt_hght * UBIFS_LPT_FANOUT_SHIFT;
	for (h = 1; h < c->lpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
		shft -= UBIFS_LPT_FANOUT_SHIFT;
		nnode = ubifs_get_nnode(c, nnode, iip);
		if (IS_ERR(nnode))
			return ERR_PTR(PTR_ERR(nnode));
		nnode = dirty_cow_nnode(c, nnode);
		if (IS_ERR(nnode))
			return ERR_PTR(PTR_ERR(nnode));
	}
	iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
	shft -= UBIFS_LPT_FANOUT_SHIFT;
	pnode = ubifs_get_pnode(c, nnode, iip);
	if (IS_ERR(pnode))
		return ERR_PTR(PTR_ERR(pnode));
	pnode = dirty_cow_pnode(c, pnode);
	if (IS_ERR(pnode))
		return ERR_PTR(PTR_ERR(pnode));
	iip = (i & (UBIFS_LPT_FANOUT - 1));
	dbg_lp("LEB %d, free %d, dirty %d, flags %d", lnum,
	       pnode->lprops[iip].free, pnode->lprops[iip].dirty,
	       pnode->lprops[iip].flags);
	ubifs_assert(test_bit(DIRTY_CNODE, &pnode->flags));
	return &pnode->lprops[iip];
}