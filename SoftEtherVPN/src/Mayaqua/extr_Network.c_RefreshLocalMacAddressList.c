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
 int /*<<< orphan*/  FreeNicList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNicList () ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * local_mac_list ; 
 int /*<<< orphan*/  local_mac_list_lock ; 

void RefreshLocalMacAddressList()
{
	Lock(local_mac_list_lock);
	{
		if (local_mac_list != NULL)
		{
			FreeNicList(local_mac_list);
		}

		local_mac_list = GetNicList();
	}
	Unlock(local_mac_list_lock);
}