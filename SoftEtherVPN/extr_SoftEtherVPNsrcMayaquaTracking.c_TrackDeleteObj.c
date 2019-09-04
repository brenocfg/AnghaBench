#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  TRACKING_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  DeleteTrackingList (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IsMemCheck () ; 
 scalar_t__ IsTrackingEnabled () ; 
 int /*<<< orphan*/  LockTrackingList () ; 
 int /*<<< orphan*/ * SearchTrackingList (scalar_t__) ; 
 int /*<<< orphan*/  UnlockTrackingList () ; 

void TrackDeleteObj(UINT64 addr)
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
			Debug("TrackDeleteObj(): 0x%x not found in tracking list!\n", addr);
			return;
		}
		DeleteTrackingList(o, true);
	}
	UnlockTrackingList();
}