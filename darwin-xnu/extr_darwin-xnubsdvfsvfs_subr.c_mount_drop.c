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
struct TYPE_5__ {scalar_t__ mnt_count; int mnt_lflag; } ;

/* Variables and functions */
 int MNT_LDRAIN ; 
 int /*<<< orphan*/  mount_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
mount_drop(mount_t mp, int locked)
{
        if ( !locked)
	        mount_lock_spin(mp);
	
	mp->mnt_count--;

	if (mp->mnt_count == 0 && (mp->mnt_lflag & MNT_LDRAIN))
	        wakeup(&mp->mnt_lflag);

        if ( !locked)
	        mount_unlock(mp);
}