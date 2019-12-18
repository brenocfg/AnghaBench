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
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 scalar_t__ IPSET_INVALID_ID ; 
 int /*<<< orphan*/  __ip_set_get (scalar_t__) ; 
 scalar_t__* ip_set_list ; 
 scalar_t__ ip_set_max ; 
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 

ip_set_id_t
ip_set_nfnl_get_byindex(ip_set_id_t index)
{
	if (index > ip_set_max)
		return IPSET_INVALID_ID;

	nfnl_lock();
	if (ip_set_list[index])
		__ip_set_get(index);
	else
		index = IPSET_INVALID_ID;
	nfnl_unlock();

	return index;
}