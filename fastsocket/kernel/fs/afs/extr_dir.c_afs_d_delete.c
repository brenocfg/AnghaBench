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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {int d_flags; scalar_t__ d_inode; TYPE_1__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_2__* AFS_FS_I (scalar_t__) ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int DCACHE_NFSFS_RENAMED ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_d_delete(struct dentry *dentry)
{
	_enter("%s", dentry->d_name.name);

	if (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		goto zap;

	if (dentry->d_inode &&
	    test_bit(AFS_VNODE_DELETED, &AFS_FS_I(dentry->d_inode)->flags))
			goto zap;

	_leave(" = 0 [keep]");
	return 0;

zap:
	_leave(" = 1 [zap]");
	return 1;
}