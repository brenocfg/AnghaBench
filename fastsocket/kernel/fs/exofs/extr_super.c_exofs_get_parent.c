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
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exofs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long exofs_parent_ino (struct dentry*) ; 

struct dentry *exofs_get_parent(struct dentry *child)
{
	unsigned long ino = exofs_parent_ino(child);

	if (!ino)
		return NULL;

	return d_obtain_alias(exofs_iget(child->d_inode->i_sb, ino));
}