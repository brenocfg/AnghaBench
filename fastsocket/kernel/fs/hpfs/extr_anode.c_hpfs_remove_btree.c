#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_7__ {TYPE_2__* internal; TYPE_1__* external; } ;
struct bplus_header {int n_used_nodes; TYPE_3__ u; scalar_t__ internal; } ;
struct anode {scalar_t__ up; struct bplus_header btree; } ;
typedef  scalar_t__ anode_secno ;
struct TYPE_8__ {scalar_t__ sb_chk; } ;
struct TYPE_6__ {scalar_t__ down; } ;
struct TYPE_5__ {scalar_t__ disk_secno; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,scalar_t__,int) ; 
 struct anode* hpfs_map_anode (struct super_block*,scalar_t__,struct buffer_head**) ; 
 TYPE_4__* hpfs_sb (struct super_block*) ; 
 scalar_t__ hpfs_stop_cycles (struct super_block*,scalar_t__,int*,int*,char*) ; 

void hpfs_remove_btree(struct super_block *s, struct bplus_header *btree)
{
	struct bplus_header *btree1 = btree;
	struct anode *anode = NULL;
	anode_secno ano = 0, oano;
	struct buffer_head *bh;
	int level = 0;
	int pos = 0;
	int i;
	int c1, c2 = 0;
	int d1, d2;
	go_down:
	d2 = 0;
	while (btree1->internal) {
		ano = btree1->u.internal[pos].down;
		if (level) brelse(bh);
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycles(s, ano, &d1, &d2, "hpfs_remove_btree #1"))
				return;
		if (!(anode = hpfs_map_anode(s, ano, &bh))) return;
		btree1 = &anode->btree;
		level++;
		pos = 0;
	}
	for (i = 0; i < btree1->n_used_nodes; i++)
		hpfs_free_sectors(s, btree1->u.external[i].disk_secno, btree1->u.external[i].length);
	go_up:
	if (!level) return;
	brelse(bh);
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycles(s, ano, &c1, &c2, "hpfs_remove_btree #2")) return;
	hpfs_free_sectors(s, ano, 1);
	oano = ano;
	ano = anode->up;
	if (--level) {
		if (!(anode = hpfs_map_anode(s, ano, &bh))) return;
		btree1 = &anode->btree;
	} else btree1 = btree;
	for (i = 0; i < btree1->n_used_nodes; i++) {
		if (btree1->u.internal[i].down == oano) {
			if ((pos = i + 1) < btree1->n_used_nodes)
				goto go_down;
			else
				goto go_up;
		}
	}
	hpfs_error(s,
		   "reference to anode %08x not found in anode %08x "
		   "(probably bad up pointer)",
		   oano, level ? ano : -1);
	if (level)
		brelse(bh);
}