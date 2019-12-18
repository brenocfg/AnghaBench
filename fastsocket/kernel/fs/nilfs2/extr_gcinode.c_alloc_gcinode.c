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
struct the_nilfs {int dummy; } ;
struct nilfs_inode_info {int i_state; int /*<<< orphan*/  i_bmap; int /*<<< orphan*/ * i_bh; scalar_t__ i_flags; int /*<<< orphan*/  i_cno; } ;
struct inode {TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int NILFS_I_GCINODE ; 
 int /*<<< orphan*/  def_gcinode_aops ; 
 int /*<<< orphan*/  nilfs_bmap_init_gc (int /*<<< orphan*/ ) ; 
 struct inode* nilfs_mdt_new_common (struct the_nilfs*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *alloc_gcinode(struct the_nilfs *nilfs, ino_t ino,
				   __u64 cno)
{
	struct inode *inode = nilfs_mdt_new_common(nilfs, NULL, ino, GFP_NOFS);
	struct nilfs_inode_info *ii;

	if (!inode)
		return NULL;

	inode->i_op = NULL;
	inode->i_fop = NULL;
	inode->i_mapping->a_ops = &def_gcinode_aops;

	ii = NILFS_I(inode);
	ii->i_cno = cno;
	ii->i_flags = 0;
	ii->i_state = 1 << NILFS_I_GCINODE;
	ii->i_bh = NULL;
	nilfs_bmap_init_gc(ii->i_bmap);

	return inode;
}