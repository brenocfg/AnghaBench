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
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct autofs_sb_info {int dummy; } ;
struct TYPE_4__ {int may_umount; } ;
struct autofs_dev_ioctl {TYPE_2__ askumount; } ;

/* Variables and functions */
 scalar_t__ may_umount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int autofs_dev_ioctl_askumount(struct file *fp,
				      struct autofs_sb_info *sbi,
				      struct autofs_dev_ioctl *param)
{
	param->askumount.may_umount = 0;
	if (may_umount(fp->f_path.mnt))
		param->askumount.may_umount = 1;
	return 0;
}