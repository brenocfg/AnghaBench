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
typedef  int u16 ;
struct hfs_bnode {scalar_t__ type; TYPE_1__* tree; } ;
struct TYPE_2__ {int attributes; int max_key_len; int node_size; } ;

/* Variables and functions */
 scalar_t__ HFS_NODE_INDEX ; 
 scalar_t__ HFS_NODE_LEAF ; 
 int HFS_TREE_BIGKEYS ; 
 int HFS_TREE_VARIDXKEYS ; 
 int hfs_bnode_read_u16 (struct hfs_bnode*,int) ; 
 int hfs_bnode_read_u8 (struct hfs_bnode*,int) ; 

u16 hfs_brec_keylen(struct hfs_bnode *node, u16 rec)
{
	u16 retval, recoff;

	if (node->type != HFS_NODE_INDEX && node->type != HFS_NODE_LEAF)
		return 0;

	if ((node->type == HFS_NODE_INDEX) &&
	   !(node->tree->attributes & HFS_TREE_VARIDXKEYS)) {
		retval = node->tree->max_key_len + 2;
	} else {
		recoff = hfs_bnode_read_u16(node, node->tree->node_size - (rec + 1) * 2);
		if (!recoff)
			return 0;
		if (node->tree->attributes & HFS_TREE_BIGKEYS)
			retval = hfs_bnode_read_u16(node, recoff) + 2;
		else
			retval = (hfs_bnode_read_u8(node, recoff) | 1) + 1;
	}
	return retval;
}