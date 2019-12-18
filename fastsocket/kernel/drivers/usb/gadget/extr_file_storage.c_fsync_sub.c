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
struct lun {scalar_t__ ro; struct file* filp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int vfs_fsync (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fsync_sub(struct lun *curlun)
{
	struct file	*filp = curlun->filp;

	if (curlun->ro || !filp)
		return 0;
	return vfs_fsync(filp, filp->f_path.dentry, 1);
}