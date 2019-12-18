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
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_inode; TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  NFSIOS_VFSFSYNC ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_inc_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_fsync_dir(struct file *filp, struct dentry *dentry, int datasync)
{
	dfprintk(FILE, "NFS: fsync dir(%s/%s) datasync %d\n",
			dentry->d_parent->d_name.name, dentry->d_name.name,
			datasync);

	nfs_inc_stats(dentry->d_inode, NFSIOS_VFSFSYNC);
	return 0;
}