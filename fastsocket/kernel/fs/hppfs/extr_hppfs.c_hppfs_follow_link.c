#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nameidata {int dummy; } ;
struct dentry {TYPE_3__* d_inode; } ;
struct TYPE_6__ {TYPE_1__* i_op; } ;
struct TYPE_5__ {struct dentry* proc_dentry; } ;
struct TYPE_4__ {void* (* follow_link ) (struct dentry*,struct nameidata*) ;} ;

/* Variables and functions */
 TYPE_2__* HPPFS_I (TYPE_3__*) ; 
 void* stub1 (struct dentry*,struct nameidata*) ; 

__attribute__((used)) static void *hppfs_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct dentry *proc_dentry;

	proc_dentry = HPPFS_I(dentry->d_inode)->proc_dentry;

	return proc_dentry->d_inode->i_op->follow_link(proc_dentry, nd);
}