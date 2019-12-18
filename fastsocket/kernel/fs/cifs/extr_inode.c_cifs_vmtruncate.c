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
struct inode {TYPE_1__* i_op; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_size; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* truncate ) (struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int inode_newsize_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cifs_vmtruncate(struct inode *inode, loff_t offset)
{
	loff_t oldsize;
	int err;

	spin_lock(&inode->i_lock);
	err = inode_newsize_ok(inode, offset);
	if (err) {
		spin_unlock(&inode->i_lock);
		goto out;
	}

	oldsize = inode->i_size;
	i_size_write(inode, offset);
	spin_unlock(&inode->i_lock);
	truncate_pagecache(inode, oldsize, offset);
	if (inode->i_op->truncate)
		inode->i_op->truncate(inode);
out:
	return err;
}