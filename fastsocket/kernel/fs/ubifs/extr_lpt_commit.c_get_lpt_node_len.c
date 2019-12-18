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
struct ubifs_info {int nnode_sz; int pnode_sz; int ltab_sz; int lsave_sz; } ;

/* Variables and functions */
#define  UBIFS_LPT_LSAVE 131 
#define  UBIFS_LPT_LTAB 130 
#define  UBIFS_LPT_NNODE 129 
#define  UBIFS_LPT_PNODE 128 

__attribute__((used)) static int get_lpt_node_len(const struct ubifs_info *c, int node_type)
{
	switch (node_type) {
	case UBIFS_LPT_NNODE:
		return c->nnode_sz;
	case UBIFS_LPT_PNODE:
		return c->pnode_sz;
	case UBIFS_LPT_LTAB:
		return c->ltab_sz;
	case UBIFS_LPT_LSAVE:
		return c->lsave_sz;
	}
	return 0;
}