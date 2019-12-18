#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Server; int /*<<< orphan*/  CurrentRegionLock; int /*<<< orphan*/  CurrentRegion; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  FlushServerCaps (int /*<<< orphan*/ ) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiUpdateCurrentRegion(CEDAR *c, char *region, bool force_update)
{
	bool changed = false;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	if (IsEmptyStr(region) == false)
	{
		Lock(c->CurrentRegionLock);
		{
			if (StrCmpi(c->CurrentRegion, region) != 0)
			{
				StrCpy(c->CurrentRegion, sizeof(c->CurrentRegion), region);
				changed = true;
			}
		}
		Unlock(c->CurrentRegionLock);
	}

	if (force_update)
	{
		changed = true;
	}

	if (changed)
	{
		FlushServerCaps(c->Server);
	}
}