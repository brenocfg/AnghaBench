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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int n_free_nodes; int first_free; scalar_t__ n_used_nodes; } ;
struct anode {TYPE_1__ btree; int /*<<< orphan*/  self; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  secno ;
typedef  int /*<<< orphan*/  anode_secno ;

/* Variables and functions */
 int /*<<< orphan*/  ANODE_ALLOC_FWD ; 
 int /*<<< orphan*/  ANODE_MAGIC ; 
 int /*<<< orphan*/  hpfs_alloc_sector (struct super_block*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hpfs_free_sectors (struct super_block*,int /*<<< orphan*/ ,int) ; 
 struct anode* hpfs_get_sector (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  memset (struct anode*,int /*<<< orphan*/ ,int) ; 

struct anode *hpfs_alloc_anode(struct super_block *s, secno near, anode_secno *ano,
			  struct buffer_head **bh)
{
	struct anode *a;
	if (!(*ano = hpfs_alloc_sector(s, near, 1, ANODE_ALLOC_FWD, 1))) return NULL;
	if (!(a = hpfs_get_sector(s, *ano, bh))) {
		hpfs_free_sectors(s, *ano, 1);
		return NULL;
	}
	memset(a, 0, 512);
	a->magic = ANODE_MAGIC;
	a->self = *ano;
	a->btree.n_free_nodes = 40;
	a->btree.n_used_nodes = 0;
	a->btree.first_free = 8;
	return a;
}