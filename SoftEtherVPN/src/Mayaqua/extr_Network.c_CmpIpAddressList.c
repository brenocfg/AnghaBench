#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ ipv6_scope_id; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 scalar_t__ COMPARE_RET (scalar_t__,scalar_t__) ; 
 scalar_t__ CmpIpAddr (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ IsIP6 (TYPE_1__*) ; 
 int IsLocalHostIP (TYPE_1__*) ; 
 int IsZeroIP (TYPE_1__*) ; 

int CmpIpAddressList(void *p1, void *p2)
{
	IP *ip1, *ip2;
	UINT r;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	ip1 = *(IP **)p1;
	ip2 = *(IP **)p2;
	if (ip1 == NULL || ip2 == NULL)
	{
		return 0;
	}

	// IPv4 < IPv6
	r = COMPARE_RET(IsIP6(ip1), IsIP6(ip2));
	if (r != 0)
	{
		return r;
	}

	// any > specified IP
	if (IsZeroIP(ip1) && IsZeroIP(ip2) == false)
	{
		return 1;
	}
	if (IsZeroIP(ip1) == false && IsZeroIP(ip2))
	{
		return -1;
	}

	// local > others
	if (IsLocalHostIP(ip1) && IsLocalHostIP(ip2) == false)
	{
		return 1;
	}
	if (IsLocalHostIP(ip1) == false && IsLocalHostIP(ip2))
	{
		return -1;
	}

	// ip address
	r = CmpIpAddr(ip1, ip2);
	if (r != 0)
	{
		return r;
	}

	// interface index
	if (IsIP6(ip1))
	{
		r = COMPARE_RET(ip1->ipv6_scope_id, ip2->ipv6_scope_id);
	}
	else
	{
		r = 0;
	}

	return r;
}