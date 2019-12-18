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
 int IsMacAddressLocalInner (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RefreshLocalMacAddressList () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * local_mac_list ; 
 int /*<<< orphan*/  local_mac_list_lock ; 

bool IsMacAddressLocalFast(void *addr)
{
	bool ret = false;
	// Validate arguments
	if (addr == NULL)
	{
		return false;
	}

	Lock(local_mac_list_lock);
	{
		if (local_mac_list == NULL)
		{
			// First enumeration
			RefreshLocalMacAddressList();
		}

		ret = IsMacAddressLocalInner(local_mac_list, addr);
	}
	Unlock(local_mac_list_lock);

	return ret;
}