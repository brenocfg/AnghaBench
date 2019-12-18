#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {scalar_t__ Address; int /*<<< orphan*/  Size; } ;
typedef  TYPE_1__ TRACKING_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteTrackingList (TYPE_1__*,int) ; 
 int /*<<< orphan*/  InsertTrackingList (TYPE_1__*) ; 
 scalar_t__ IsMemCheck () ; 
 scalar_t__ IsTrackingEnabled () ; 
 int /*<<< orphan*/  LockTrackingList () ; 
 TYPE_1__* SearchTrackingList (scalar_t__) ; 
 int /*<<< orphan*/  UnlockTrackingList () ; 

void TrackChangeObjSize(UINT64 addr, UINT size, UINT64 new_addr)
{
	TRACKING_OBJECT *o;
	// Validate arguments
	if (addr == 0)
	{
		return;
	}

	if ((IsTrackingEnabled() && IsMemCheck()) == false)
	{
		// Don't track in detail if the memory check option is not specified
		return;
	}

	LockTrackingList();
	{
		o = SearchTrackingList(addr);
		if (o == NULL)
		{
			UnlockTrackingList();
			return;
		}

		DeleteTrackingList(o, false);

		o->Size = size;
		o->Address = new_addr;

		InsertTrackingList(o);
	}
	UnlockTrackingList();
}