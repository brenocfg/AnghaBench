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
struct ubifs_info {int lpt_hght; struct ubifs_nnode* nroot; } ;

/* Variables and functions */
 struct ubifs_pnode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ubifs_nnode*) ; 
 int PTR_ERR (struct ubifs_nnode*) ; 
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 
 struct ubifs_nnode* ubifs_get_nnode (struct ubifs_info*,struct ubifs_nnode*,int) ; 
 struct ubifs_pnode* ubifs_get_pnode (struct ubifs_info*,struct ubifs_nnode*,int) ; 
 int ubifs_read_nnode (struct ubifs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ubifs_pnode *pnode_lookup(struct ubifs_info *c, int i)
{
	int err, h, iip, shft;
	struct ubifs_nnode *nnode;

	if (!c->nroot) {
		err = ubifs_read_nnode(c, NULL, 0);
		if (err)
			return ERR_PTR(err);
	}
	i <<= UBIFS_LPT_FANOUT_SHIFT;
	nnode = c->nroot;
	shft = c->lpt_hght * UBIFS_LPT_FANOUT_SHIFT;
	for (h = 1; h < c->lpt_hght; h++) {
		iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
		shft -= UBIFS_LPT_FANOUT_SHIFT;
		nnode = ubifs_get_nnode(c, nnode, iip);
		if (IS_ERR(nnode))
			return ERR_PTR(PTR_ERR(nnode));
	}
	iip = ((i >> shft) & (UBIFS_LPT_FANOUT - 1));
	return ubifs_get_pnode(c, nnode, iip);
}