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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct anode {int /*<<< orphan*/  btree; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,int /*<<< orphan*/ ,unsigned int) ; 
 struct anode* hpfs_map_anode (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_remove_btree (struct super_block*,int /*<<< orphan*/ *) ; 

void hpfs_ea_remove(struct super_block *s, secno a, int ano, unsigned len)
{
	struct anode *anode;
	struct buffer_head *bh;
	if (ano) {
		if (!(anode = hpfs_map_anode(s, a, &bh))) return;
		hpfs_remove_btree(s, &anode->btree);
		brelse(bh);
		hpfs_free_sectors(s, a, 1);
	} else hpfs_free_sectors(s, a, (len + 511) >> 9);
}