#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mount_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_list ; 
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int /*<<< orphan*/  mountlist ; 
 int /*<<< orphan*/  nummounts ; 
 scalar_t__ system_inshutdown ; 

int
mount_list_add(mount_t mp)
{
	int res;

	mount_list_lock();
	if (system_inshutdown != 0) {
		res = -1;
	} else {
		TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);	
		nummounts++;
		res = 0;
	}
	mount_list_unlock();

	return res;
}