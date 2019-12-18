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
struct super_block {int /*<<< orphan*/  s_root; } ;
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct TYPE_2__ {int /*<<< orphan*/ * i_ctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 TYPE_1__* SPUFS_I (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_alloc_root (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 int /*<<< orphan*/  spu_management_ops ; 
 struct inode* spufs_new_inode (struct super_block*,int) ; 
 int /*<<< orphan*/  spufs_parse_options (struct super_block*,void*,struct inode*) ; 

__attribute__((used)) static int
spufs_create_root(struct super_block *sb, void *data)
{
	struct inode *inode;
	int ret;

	ret = -ENODEV;
	if (!spu_management_ops)
		goto out;

	ret = -ENOMEM;
	inode = spufs_new_inode(sb, S_IFDIR | 0775);
	if (!inode)
		goto out;

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	SPUFS_I(inode)->i_ctx = NULL;
	inc_nlink(inode);

	ret = -EINVAL;
	if (!spufs_parse_options(sb, data, inode))
		goto out_iput;

	ret = -ENOMEM;
	sb->s_root = d_alloc_root(inode);
	if (!sb->s_root)
		goto out_iput;

	return 0;
out_iput:
	iput(inode);
out:
	return ret;
}