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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {scalar_t__ VlanId; scalar_t__* MacAddress; } ;
typedef  TYPE_1__ MAC_TABLE_ENTRY ;

/* Variables and functions */

UINT GetHashOfMacTable(void *p)
{
	UINT v;
	MAC_TABLE_ENTRY *e = p;

	if (e == NULL)
	{
		return 0;
	}

	v = e->MacAddress[0] + e->MacAddress[1] + e->MacAddress[2] + 
		e->MacAddress[3] + e->MacAddress[4] + e->MacAddress[5] + 
		e->VlanId;

	return v;
}