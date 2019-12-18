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
struct dentry {TYPE_1__* d_inode; } ;
typedef  scalar_t__ efs_ino_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 scalar_t__ efs_find_entry (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  efs_iget (int /*<<< orphan*/ ,scalar_t__) ; 

struct dentry *efs_get_parent(struct dentry *child)
{
	struct dentry *parent = ERR_PTR(-ENOENT);
	efs_ino_t ino;

	ino = efs_find_entry(child->d_inode, "..", 2);
	if (ino)
		parent = d_obtain_alias(efs_iget(child->d_inode->i_sb, ino));

	return parent;
}