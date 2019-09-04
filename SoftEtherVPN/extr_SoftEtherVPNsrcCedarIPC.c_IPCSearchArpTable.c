#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ArpTable; } ;
struct TYPE_7__ {int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ IPC_ARP ;
typedef  TYPE_2__ IPC ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 

IPC_ARP *IPCSearchArpTable(IPC *ipc, IP *ip)
{
	IPC_ARP t;
	IPC_ARP *a;
	// Validate arguments
	if (ipc == NULL || ip == NULL)
	{
		return NULL;
	}

	Copy(&t.Ip, ip, sizeof(IP));

	a = Search(ipc->ArpTable, &t);

	return a;
}