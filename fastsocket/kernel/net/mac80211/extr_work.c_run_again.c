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
struct ieee80211_local {TYPE_1__ work_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WORK_MTX (struct ieee80211_local*) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,unsigned long) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void run_again(struct ieee80211_local *local,
		      unsigned long timeout)
{
	ASSERT_WORK_MTX(local);

	if (!timer_pending(&local->work_timer) ||
	    time_before(timeout, local->work_timer.expires))
		mod_timer(&local->work_timer, timeout);
}