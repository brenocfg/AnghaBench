#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ipv6_scope_id; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetPrefixAddress6 (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int IsIP6 (TYPE_1__*) ; 

bool IsInSameNetwork6(IP *a1, IP *a2, IP *subnet)
{
	IP prefix1, prefix2;
	// Validate arguments
	if (IsIP6(a1) == false || IsIP6(a2) == false || IsIP6(subnet) == false)
	{
		return false;
	}

	if (a1->ipv6_scope_id != a2->ipv6_scope_id)
	{
		return false;
	}

	GetPrefixAddress6(&prefix1, a1, subnet);
	GetPrefixAddress6(&prefix2, a2, subnet);

	if (CmpIpAddr(&prefix1, &prefix2) == 0)
	{
		return true;
	}

	return false;
}