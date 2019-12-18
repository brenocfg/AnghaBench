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
struct TYPE_2__ {int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ IPC_ARP ;

/* Variables and functions */
 int CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int IPCCmpArpTable(void *p1, void *p2)
{
	IPC_ARP *a1, *a2;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	a1 = *(IPC_ARP **)p1;
	a2 = *(IPC_ARP **)p2;
	if (a1 == NULL || a2 == NULL)
	{
		return 0;
	}

	return CmpIpAddr(&a1->Ip, &a2->Ip);
}