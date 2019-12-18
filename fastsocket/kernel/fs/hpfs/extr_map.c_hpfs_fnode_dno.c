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
struct TYPE_4__ {TYPE_1__* external; } ;
struct fnode {TYPE_2__ u; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  dnode_secno ;
struct TYPE_3__ {int /*<<< orphan*/  disk_secno; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct fnode* hpfs_map_fnode (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**) ; 

dnode_secno hpfs_fnode_dno(struct super_block *s, ino_t ino)
{
	struct buffer_head *bh;
	struct fnode *fnode;
	dnode_secno dno;

	fnode = hpfs_map_fnode(s, ino, &bh);
	if (!fnode)
		return 0;

	dno = fnode->u.external[0].disk_secno;
	brelse(bh);
	return dno;
}