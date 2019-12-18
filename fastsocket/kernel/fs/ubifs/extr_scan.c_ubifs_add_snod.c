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
struct ubifs_scan_node {int type; int offs; int /*<<< orphan*/  list; int /*<<< orphan*/  key; void* node; int /*<<< orphan*/  len; int /*<<< orphan*/  sqnum; } ;
struct ubifs_scan_leb {int nodes_cnt; int /*<<< orphan*/  nodes; } ;
struct ubifs_ino_node {int /*<<< orphan*/  key; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_ch {int node_type; int /*<<< orphan*/  len; int /*<<< orphan*/  sqnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
#define  UBIFS_DATA_NODE 132 
#define  UBIFS_DENT_NODE 131 
#define  UBIFS_INO_NODE 130 
#define  UBIFS_TRUN_NODE 129 
#define  UBIFS_XENT_NODE 128 
 int /*<<< orphan*/  key_read (struct ubifs_info const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ubifs_scan_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ubifs_add_snod(const struct ubifs_info *c, struct ubifs_scan_leb *sleb,
		   void *buf, int offs)
{
	struct ubifs_ch *ch = buf;
	struct ubifs_ino_node *ino = buf;
	struct ubifs_scan_node *snod;

	snod = kzalloc(sizeof(struct ubifs_scan_node), GFP_NOFS);
	if (!snod)
		return -ENOMEM;

	snod->sqnum = le64_to_cpu(ch->sqnum);
	snod->type = ch->node_type;
	snod->offs = offs;
	snod->len = le32_to_cpu(ch->len);
	snod->node = buf;

	switch (ch->node_type) {
	case UBIFS_INO_NODE:
	case UBIFS_DENT_NODE:
	case UBIFS_XENT_NODE:
	case UBIFS_DATA_NODE:
	case UBIFS_TRUN_NODE:
		/*
		 * The key is in the same place in all keyed
		 * nodes.
		 */
		key_read(c, &ino->key, &snod->key);
		break;
	}
	list_add_tail(&snod->list, &sleb->nodes);
	sleb->nodes_cnt += 1;
	return 0;
}