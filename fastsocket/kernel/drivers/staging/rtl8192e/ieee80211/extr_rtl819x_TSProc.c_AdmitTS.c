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
typedef  scalar_t__ u32 ;
struct ieee80211_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  InactTimer; int /*<<< orphan*/  SetupTimer; } ;
typedef  TYPE_1__* PTS_COMMON_INFO ;

/* Variables and functions */
 scalar_t__ MSECS (scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void AdmitTS(struct ieee80211_device *ieee, PTS_COMMON_INFO pTsCommonInfo, u32 InactTime)
{
	del_timer_sync(&pTsCommonInfo->SetupTimer);
	del_timer_sync(&pTsCommonInfo->InactTimer);

	if(InactTime!=0)
		mod_timer(&pTsCommonInfo->InactTimer, jiffies + MSECS(InactTime));
}