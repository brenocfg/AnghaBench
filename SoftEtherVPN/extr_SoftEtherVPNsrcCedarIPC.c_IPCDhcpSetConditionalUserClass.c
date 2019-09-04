#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  UserClass; } ;
struct TYPE_11__ {TYPE_1__* Option; } ;
struct TYPE_10__ {int /*<<< orphan*/  HubName; int /*<<< orphan*/  Cedar; } ;
struct TYPE_9__ {scalar_t__ UseHubNameAsDhcpUserClassOption; } ;
typedef  TYPE_2__ IPC ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ DHCP_OPTION_LIST ;

/* Variables and functions */
 TYPE_3__* GetHub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void IPCDhcpSetConditionalUserClass(IPC *ipc, DHCP_OPTION_LIST *req)
{
	HUB *hub;

	hub = GetHub(ipc->Cedar, ipc->HubName);
	if (hub == NULL)
	{
		return;
	}

	if (hub->Option && hub->Option->UseHubNameAsDhcpUserClassOption)
	{
		StrCpy(req->UserClass, sizeof(req->UserClass), ipc->HubName);
	}
	ReleaseHub(hub);
}