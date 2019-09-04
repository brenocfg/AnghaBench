#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  TYPE_1__* mount_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {int /*<<< orphan*/  mnt_fsgroup; int /*<<< orphan*/  mnt_fsowner; } ;

/* Variables and functions */

void vfs_setowner(mount_t mp, uid_t uid, gid_t gid)
{
	mp->mnt_fsowner = uid;
	mp->mnt_fsgroup = gid;
}