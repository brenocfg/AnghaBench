#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int MonitorPort; void* GroupnameHash; void* UsernameHash; int /*<<< orphan*/  StormList; TYPE_4__* Session; int /*<<< orphan*/  Now; int /*<<< orphan*/  PacketQueue; int /*<<< orphan*/  Cancel; } ;
struct TYPE_12__ {TYPE_3__* Hub; TYPE_2__* Policy; TYPE_1__* PacketAdapter; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Username; } ;
struct TYPE_11__ {int /*<<< orphan*/  MonitorList; } ;
struct TYPE_10__ {scalar_t__ MonitorPort; } ;
struct TYPE_9__ {TYPE_5__* Param; } ;
typedef  TYPE_4__ SESSION ;
typedef  TYPE_5__ HUB_PA ;

/* Variables and functions */
 int /*<<< orphan*/  CompareStormList ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewCancel () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 void* UsernameToInt64 (int /*<<< orphan*/ ) ; 
 TYPE_5__* ZeroMalloc (int) ; 

bool HubPaInit(SESSION *s)
{
	// Initialize the packet adapter information
	HUB_PA *pa = ZeroMalloc(sizeof(HUB_PA));
	pa->Cancel = NewCancel();
	pa->PacketQueue = NewQueue();
	pa->Now = Tick64();
	pa->Session = s;
	pa->StormList = NewList(CompareStormList);
	pa->UsernameHash = UsernameToInt64(s->Username);
	pa->GroupnameHash = UsernameToInt64(s->GroupName);

	s->PacketAdapter->Param = pa;

	if (s->Policy->MonitorPort)
	{
		// Mark this port as monitoring port
		pa->MonitorPort = true;

		// Add this session to the list of monitoring port of the HUB
		LockList(s->Hub->MonitorList);
		{
			Insert(s->Hub->MonitorList, s);
		}
		UnlockList(s->Hub->MonitorList);
	}

	return true;
}