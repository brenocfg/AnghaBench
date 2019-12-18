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
struct qstr {char* name; int len; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long ext2_inode_by_name (TYPE_1__*,struct qstr*) ; 

struct dentry *ext2_get_parent(struct dentry *child)
{
	struct qstr dotdot = {.name = "..", .len = 2};
	unsigned long ino = ext2_inode_by_name(child->d_inode, &dotdot);
	if (!ino)
		return ERR_PTR(-ENOENT);
	return d_obtain_alias(ext2_iget(child->d_inode->i_sb, ino));
}