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
struct ieee80211_device {int /*<<< orphan*/  wx_sem; int /*<<< orphan*/ * pDot11dInfo; int /*<<< orphan*/  wq; int /*<<< orphan*/  GPIOChangeRFWorkItem; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  associate_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void ieee80211_softmac_free(struct ieee80211_device *ieee)
{
	down(&ieee->wx_sem);

	del_timer_sync(&ieee->associate_timer);
	cancel_delayed_work(&ieee->associate_retry_wq);


	//add for RF power on power of by lizhaoming 080512
	cancel_delayed_work(&ieee->GPIOChangeRFWorkItem);

	destroy_workqueue(ieee->wq);
	if(NULL != ieee->pDot11dInfo)
		kfree(ieee->pDot11dInfo);
	up(&ieee->wx_sem);
}