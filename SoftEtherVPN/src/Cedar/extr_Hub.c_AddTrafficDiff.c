#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int FarmMember; char* Name; TYPE_1__* Cedar; } ;
struct TYPE_8__ {int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Type; void* Name; void* HubName; } ;
struct TYPE_7__ {int /*<<< orphan*/  TrafficDiffList; } ;
typedef  TYPE_2__ TRAFFIC_DIFF ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_3__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_TRAFFIC_DIFF ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMallocFast (int) ; 

void AddTrafficDiff(HUB *h, char *name, UINT type, TRAFFIC *traffic)
{
	TRAFFIC_DIFF *d;
	// Validate arguments
	if (h == NULL || h->FarmMember == false || name == NULL || traffic == NULL)
	{
		return;
	}

	if (LIST_NUM(h->Cedar->TrafficDiffList) > MAX_TRAFFIC_DIFF)
	{
		return;
	}

	d = ZeroMallocFast(sizeof(TRAFFIC_DIFF));
	d->HubName = CopyStr(h->Name);
	d->Name = CopyStr(name);
	d->Type = type;
	Copy(&d->Traffic, traffic, sizeof(TRAFFIC));

	LockList(h->Cedar->TrafficDiffList);
	{
		Insert(h->Cedar->TrafficDiffList, d);
	}
	UnlockList(h->Cedar->TrafficDiffList);
}