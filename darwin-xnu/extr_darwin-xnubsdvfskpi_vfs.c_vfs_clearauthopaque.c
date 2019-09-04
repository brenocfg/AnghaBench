#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mount_t ;
struct TYPE_5__ {int /*<<< orphan*/  mnt_kern_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNTK_AUTH_OPAQUE ; 
 int /*<<< orphan*/  mount_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_1__*) ; 

void
vfs_clearauthopaque(mount_t mp)
{
	mount_lock(mp);
	mp->mnt_kern_flag &= ~MNTK_AUTH_OPAQUE;
	mount_unlock(mp);
}