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
struct super_block {TYPE_1__* s_qcop; } ;
struct TYPE_2__ {int (* quota_on ) (struct super_block*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int MAXQUOTAS ; 
 int stub1 (struct super_block*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int vfs_dq_quota_on_remount(struct super_block *sb)
{
	int cnt;
	int ret = 0, err;

	if (!sb->s_qcop || !sb->s_qcop->quota_on)
		return -ENOSYS;
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		err = sb->s_qcop->quota_on(sb, cnt, 0, NULL, 1);
		if (err < 0 && !ret)
			ret = err;
	}
	return ret;
}