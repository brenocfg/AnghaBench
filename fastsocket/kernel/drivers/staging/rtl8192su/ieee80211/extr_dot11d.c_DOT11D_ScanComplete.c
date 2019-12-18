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
struct ieee80211_device {int dummy; } ;
struct TYPE_3__ {int State; } ;
typedef  TYPE_1__* PRT_DOT11D_INFO ;

/* Variables and functions */
#define  DOT11D_STATE_DONE 130 
#define  DOT11D_STATE_LEARNED 129 
#define  DOT11D_STATE_NONE 128 
 int /*<<< orphan*/  Dot11d_Reset (struct ieee80211_device*) ; 
 int /*<<< orphan*/  GET_CIE_WATCHDOG (struct ieee80211_device*) ; 
 TYPE_1__* GET_DOT11D_INFO (struct ieee80211_device*) ; 

void
DOT11D_ScanComplete(
	struct ieee80211_device * dev
	)
{
	PRT_DOT11D_INFO pDot11dInfo = GET_DOT11D_INFO(dev);

	switch(pDot11dInfo->State)
	{
	case DOT11D_STATE_LEARNED:
		pDot11dInfo->State = DOT11D_STATE_DONE;
		break;

	case DOT11D_STATE_DONE:
		if( GET_CIE_WATCHDOG(dev) == 0 )
		{ // Reset country IE if previous one is gone.
			Dot11d_Reset(dev);
		}
		break;
	case DOT11D_STATE_NONE:
		break;
	}
}