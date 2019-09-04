#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_16__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_15__ {TYPE_1__* Server; } ;
struct TYPE_14__ {int /*<<< orphan*/  ref; } ;
struct TYPE_13__ {TYPE_4__* Cedar; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ HUB ;
typedef  TYPE_3__ FARM_CONTROLLER ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DelHub (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__**) ; 
 size_t LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 int /*<<< orphan*/  SetHubOffline (TYPE_2__*) ; 
 int /*<<< orphan*/  SiAcceptTasksFromControllerMain (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__** ToArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiAcceptTasksFromController(FARM_CONTROLLER *f, SOCK *sock)
{
	UINT i;
	HUB **hubs;
	UINT num_hubs;
	CEDAR *c;
	SERVER *s;
	// Validate arguments
	if (f == NULL || sock == NULL)
	{
		return;
	}

	s = f->Server;
	c = s->Cedar;

	// Main process
	SiAcceptTasksFromControllerMain(f, sock);

	// Stop all Virtual HUBs since the connection to the controller is disconnected
	LockList(c->HubList);
	{
		hubs = ToArray(c->HubList);
		num_hubs = LIST_NUM(c->HubList);
		for (i = 0;i < num_hubs;i++)
		{
			AddRef(hubs[i]->ref);
		}
	}
	UnlockList(c->HubList);

	for (i = 0;i < num_hubs;i++)
	{
		SetHubOffline(hubs[i]);
		DelHub(c, hubs[i]);
		ReleaseHub(hubs[i]);
	}

	Free(hubs);
}