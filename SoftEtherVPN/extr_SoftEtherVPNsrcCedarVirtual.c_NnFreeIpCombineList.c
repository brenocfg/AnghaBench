#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  IpCombine; } ;
typedef  TYPE_1__ NATIVE_NAT ;
typedef  int /*<<< orphan*/  IP_COMBINE ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NnFreeIpCombine (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 

void NnFreeIpCombineList(NATIVE_NAT *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(t->IpCombine);i++)
	{
		IP_COMBINE *c = LIST_DATA(t->IpCombine, i);

		NnFreeIpCombine(t, c);
	}

	ReleaseList(t->IpCombine);
}