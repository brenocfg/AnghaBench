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
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/ * CloneIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressListInternal () ; 
 scalar_t__ HOST_IP_ADDRESS_LIST_CACHE ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * host_ip_address_cache ; 
 scalar_t__ host_ip_address_list_cache_last ; 
 int /*<<< orphan*/ * host_ip_address_list_cache_lock ; 

LIST *GetHostIPAddressList()
{
	LIST *o = NULL;
	if (host_ip_address_list_cache_lock == NULL)
	{
		return GetHostIPAddressListInternal();
	}

	Lock(host_ip_address_list_cache_lock);
	{
		UINT64 now = Tick64();

		if (host_ip_address_list_cache_last == 0 ||
			((host_ip_address_list_cache_last + (UINT64)HOST_IP_ADDRESS_LIST_CACHE) < now) ||
			host_ip_address_cache == NULL)
		{
			if (host_ip_address_cache != NULL)
			{
				FreeHostIPAddressList(host_ip_address_cache);
			}

			host_ip_address_cache = GetHostIPAddressListInternal();

			host_ip_address_list_cache_last = now;
		}

		o = CloneIPAddressList(host_ip_address_cache);
	}
	Unlock(host_ip_address_list_cache_lock);

	if (o == NULL)
	{
		o = GetHostIPAddressListInternal();
	}

	return o;
}