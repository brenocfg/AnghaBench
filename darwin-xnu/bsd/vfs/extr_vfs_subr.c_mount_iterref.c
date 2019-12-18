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
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {scalar_t__ mnt_iterref; } ;

/* Variables and functions */
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 

int
mount_iterref(mount_t mp, int locked)
{
	int retval = 0;

	if (!locked)
		mount_list_lock();
	if (mp->mnt_iterref < 0) {
		retval = 1;
	} else {
		mp->mnt_iterref++;
	}
	if (!locked)
		mount_list_unlock();
	return(retval);
}