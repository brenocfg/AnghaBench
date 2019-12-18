#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_3__ {int n_used_nodes; int first_free; scalar_t__ internal; scalar_t__ n_free_nodes; } ;
struct anode {scalar_t__ magic; scalar_t__ self; TYPE_1__ btree; } ;
typedef  scalar_t__ anode_secno ;
struct TYPE_4__ {scalar_t__ sb_chk; } ;

/* Variables and functions */
 scalar_t__ ANODE_MAGIC ; 
 int /*<<< orphan*/  ANODE_RD_AHEAD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ hpfs_chk_sectors (struct super_block*,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,scalar_t__) ; 
 struct anode* hpfs_map_sector (struct super_block*,scalar_t__,struct buffer_head**,int /*<<< orphan*/ ) ; 
 TYPE_2__* hpfs_sb (struct super_block*) ; 

struct anode *hpfs_map_anode(struct super_block *s, anode_secno ano, struct buffer_head **bhp)
{
	struct anode *anode;
	if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectors(s, ano, 1, "anode")) return NULL;
	if ((anode = hpfs_map_sector(s, ano, bhp, ANODE_RD_AHEAD)))
		if (hpfs_sb(s)->sb_chk) {
			if (anode->magic != ANODE_MAGIC || anode->self != ano) {
				hpfs_error(s, "bad magic on anode %08x", ano);
				goto bail;
			}
			if ((unsigned)anode->btree.n_used_nodes + (unsigned)anode->btree.n_free_nodes !=
			    (anode->btree.internal ? 60 : 40)) {
				hpfs_error(s, "bad number of nodes in anode %08x", ano);
				goto bail;
			}
			if (anode->btree.first_free !=
			    8 + anode->btree.n_used_nodes * (anode->btree.internal ? 8 : 12)) {
				hpfs_error(s, "bad first_free pointer in anode %08x", ano);
				goto bail;
			}
		}
	return anode;
	bail:
	brelse(*bhp);
	return NULL;
}