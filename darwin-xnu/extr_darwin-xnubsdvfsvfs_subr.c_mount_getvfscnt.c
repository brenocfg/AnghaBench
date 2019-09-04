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

/* Variables and functions */
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int nummounts ; 

__attribute__((used)) static int
mount_getvfscnt(void)
{
	int ret;

	mount_list_lock();
	ret = nummounts;
	mount_list_unlock();
	return (ret);

}