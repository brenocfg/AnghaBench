#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {scalar_t__ num_item; } ;
struct TYPE_22__ {int /*<<< orphan*/  HubList; } ;
struct TYPE_21__ {int Halting; TYPE_8__* TaskQueue; int /*<<< orphan*/  TaskPostEvent; int /*<<< orphan*/  HubList; } ;
struct TYPE_20__ {int /*<<< orphan*/  CompleteEvent; int /*<<< orphan*/ * Response; int /*<<< orphan*/ * Request; } ;
struct TYPE_19__ {int Offline; scalar_t__ Type; int /*<<< orphan*/  Name; } ;
struct TYPE_18__ {int DynamicHub; int /*<<< orphan*/  Name; TYPE_5__* FarmMember; } ;
struct TYPE_17__ {scalar_t__ Halt; TYPE_6__* Cedar; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ HUB_LIST ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ FARM_TASK ;
typedef  TYPE_5__ FARM_MEMBER ;
typedef  TYPE_6__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIRM_SERV_RECV_PACK_MAX_SIZE ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 TYPE_4__* GetNext (TYPE_8__*) ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 int /*<<< orphan*/ * HttpServerRecv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpServerRecvEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int HttpServerSend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockQueue (TYPE_8__*) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int SERVER_CONTROL_TCP_TIMEOUT ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiPackAddCreateHub (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_8__*) ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void SiFarmServMain(SERVER *server, SOCK *sock, FARM_MEMBER *f)
{
	UINT wait_time = SERVER_CONTROL_TCP_TIMEOUT / 2;
	bool send_noop = false;
	UINT i;
	CEDAR *c;
	// Validate arguments
	if (server == NULL || sock == NULL || f == NULL)
	{
		Debug("SiFarmServMain Failed.\n");
		return;
	}

	Debug("SiFarmServMain Started.\n");

	c = server->Cedar;

	// Send a directive to create all static HUBs at the stage
	// where the members have been connected to the controller
	LockList(c->HubList);
	{
		for (i = 0;i < LIST_NUM(c->HubList);i++)
		{
			HUB *h = LIST_DATA(c->HubList, i);
			if (h->Offline == false)
			{
				if (h->Type == HUB_TYPE_FARM_STATIC)
				{
					PACK *p;
					HUB_LIST *hh;
					p = NewPack();
					SiPackAddCreateHub(p, h);
					PackAddStr(p, "taskname", "createhub");
					HttpServerSend(sock, p);
					FreePack(p);
					p = HttpServerRecv(sock);
					FreePack(p);

					p = NewPack();
					SiPackAddCreateHub(p, h);
					PackAddStr(p, "taskname", "updatehub");
					HttpServerSend(sock, p);
					FreePack(p);
					p = HttpServerRecv(sock);
					FreePack(p);

					hh = ZeroMalloc(sizeof(HUB_LIST));
					hh->DynamicHub = false;
					hh->FarmMember = f;
					StrCpy(hh->Name, sizeof(hh->Name), h->Name);
					LockList(f->HubList);
					{
						Add(f->HubList, hh);
					}
					UnlockList(f->HubList);
				}
			}
		}
	}
	UnlockList(c->HubList);

	Debug("SiFarmServMain: while (true)\n");

	while (true)
	{
		FARM_TASK *t;
		UINT64 tick;

		do
		{
			// Check whether a new task arrived
			LockQueue(f->TaskQueue);
			{
				t = GetNext(f->TaskQueue);
			}
			UnlockQueue(f->TaskQueue);

			if (t != NULL)
			{
				// Handle this task
				PACK *p = t->Request;
				bool ret;

				// Transmission
				ret = HttpServerSend(sock, p);
				send_noop = false;

				if (ret == false)
				{
					// Disconnected
					// Cancel this task
					Set(t->CompleteEvent);
					goto DISCONNECTED;
				}

				// Receive
				p = HttpServerRecvEx(sock, FIRM_SERV_RECV_PACK_MAX_SIZE);

				t->Response = p;
				Set(t->CompleteEvent);

				if (p == NULL)
				{
					// Avoid infinite loop
					Disconnect(sock);
					goto DISCONNECTED;
				}
			}
		}
		while (t != NULL);

		if (send_noop)
		{
			// Send a NOOP
			PACK *p;
			bool ret;
			p = NewPack();
			PackAddStr(p, "taskname", "noop");

			ret = HttpServerSend(sock, p);
			FreePack(p);

			if (ret == false)
			{
				goto DISCONNECTED;
			}

			p = HttpServerRecv(sock);
			if (p == NULL)
			{
				goto DISCONNECTED;
			}

			FreePack(p);
		}

		tick = Tick64();

		while (true)
		{
			bool break_flag;
			if ((tick + wait_time) <= Tick64())
			{
				break;
			}

			Wait(f->TaskPostEvent, 250);

			break_flag = false;
			LockQueue(f->TaskQueue);
			{
				if (f->TaskQueue->num_item != 0)
				{
					break_flag = true;
				}
			}
			UnlockQueue(f->TaskQueue);

			if (break_flag || f->Halting || server->Halt)
			{
				break;
			}
		}
		send_noop = true;
	}

DISCONNECTED:

	Debug("SiFarmServMain: DISCONNECTED\n");

	f->Halting = true;
	// Cancel all outstanding tasks
	LockQueue(f->TaskQueue);
	{
		FARM_TASK *t;

		while (t = GetNext(f->TaskQueue))
		{
			Set(t->CompleteEvent);
		}
	}
	UnlockQueue(f->TaskQueue);
}