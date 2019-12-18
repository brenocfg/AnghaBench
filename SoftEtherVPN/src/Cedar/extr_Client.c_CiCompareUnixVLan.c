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
struct TYPE_2__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ UNIX_VLAN ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CiCompareUnixVLan(void *p1, void *p2)
{
	UNIX_VLAN *v1, *v2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	v1 = *(UNIX_VLAN **)p1;
	v2 = *(UNIX_VLAN **)p2;
	if (v1 == NULL || v2 == NULL)
	{
		return 0;
	}

	return StrCmpi(v1->Name, v2->Name);
}