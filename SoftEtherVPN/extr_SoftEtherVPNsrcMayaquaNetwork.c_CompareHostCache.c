#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IpAddress; } ;
typedef  TYPE_1__ HOSTCACHE ;

/* Variables and functions */
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int CompareHostCache(void *p1, void *p2)
{
	HOSTCACHE *c1, *c2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	c1 = *(HOSTCACHE **)p1;
	c2 = *(HOSTCACHE **)p2;
	if (c1 == NULL || c2 == NULL)
	{
		return 0;
	}

	return CmpIpAddr(&c1->IpAddress, &c2->IpAddress);
}