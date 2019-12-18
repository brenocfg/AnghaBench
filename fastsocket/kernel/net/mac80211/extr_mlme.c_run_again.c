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
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;
struct ieee80211_if_managed {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_MGD_MTX (struct ieee80211_if_managed*) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void run_again(struct ieee80211_if_managed *ifmgd, unsigned long timeout)
{
	ASSERT_MGD_MTX(ifmgd);

	if (!timer_pending(&ifmgd->timer) ||
	    time_before(timeout, ifmgd->timer.expires))
		mod_timer(&ifmgd->timer, timeout);
}