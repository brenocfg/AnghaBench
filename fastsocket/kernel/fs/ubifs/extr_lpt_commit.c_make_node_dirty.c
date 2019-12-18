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
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  UBIFS_LPT_LSAVE 131 
#define  UBIFS_LPT_LTAB 130 
#define  UBIFS_LPT_NNODE 129 
#define  UBIFS_LPT_PNODE 128 
 int make_lsave_dirty (struct ubifs_info*,int,int) ; 
 int make_ltab_dirty (struct ubifs_info*,int,int) ; 
 int make_nnode_dirty (struct ubifs_info*,int,int,int) ; 
 int make_pnode_dirty (struct ubifs_info*,int,int,int) ; 

__attribute__((used)) static int make_node_dirty(struct ubifs_info *c, int node_type, int node_num,
			   int lnum, int offs)
{
	switch (node_type) {
	case UBIFS_LPT_NNODE:
		return make_nnode_dirty(c, node_num, lnum, offs);
	case UBIFS_LPT_PNODE:
		return make_pnode_dirty(c, node_num, lnum, offs);
	case UBIFS_LPT_LTAB:
		return make_ltab_dirty(c, lnum, offs);
	case UBIFS_LPT_LSAVE:
		return make_lsave_dirty(c, lnum, offs);
	}
	return -EINVAL;
}