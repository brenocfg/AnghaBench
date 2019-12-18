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
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int d_flags; } ;

/* Variables and functions */
 int DCACHE_FASTSOCKET ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fastsocket_release(struct inode *inode, struct file *filp)
{
	DPRINTK(DEBUG, "Enter fsocket_release. inode(%p) file(%p) dentry(%p)", 
		inode, filp, filp->f_path.dentry);

	if (filp->f_path.dentry->d_flags & DCACHE_FASTSOCKET) {
		DPRINTK(INFO, "dentry memleak happens!!!\n");
	}

	module_put(THIS_MODULE);

	DPRINTK(INFO, "Release module reference\n");

	return 0;
}