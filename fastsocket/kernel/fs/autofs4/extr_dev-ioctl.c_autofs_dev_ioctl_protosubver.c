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
struct file {int dummy; } ;
struct autofs_sb_info {int /*<<< orphan*/  sub_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  sub_version; } ;
struct autofs_dev_ioctl {TYPE_1__ protosubver; } ;

/* Variables and functions */

__attribute__((used)) static int autofs_dev_ioctl_protosubver(struct file *fp,
					struct autofs_sb_info *sbi,
					struct autofs_dev_ioctl *param)
{
	param->protosubver.sub_version = sbi->sub_version;
	return 0;
}