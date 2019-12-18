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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {char* CurrentRegion; int /*<<< orphan*/  CurrentRegionLock; } ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentLangId () ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 scalar_t__ SE_LANG_CHINESE_ZH ; 
 scalar_t__ SE_LANG_JAPANESE ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiGetCurrentRegion(CEDAR *c, char *region, UINT region_size)
{
	ClearStr(region, region_size);
	// Validate arguments
	if (c == NULL || region == NULL)
	{
		return;
	}

	Lock(c->CurrentRegionLock);
	{
		StrCpy(region, region_size, c->CurrentRegion);
	}
	Unlock(c->CurrentRegionLock);

	if (IsEmptyStr(region))
	{
		if (GetCurrentLangId() == SE_LANG_JAPANESE)
		{
			StrCpy(region, region_size, "JP");
		}
		else if (GetCurrentLangId() == SE_LANG_CHINESE_ZH)
		{
			StrCpy(region, region_size, "CN");
		}
	}
}