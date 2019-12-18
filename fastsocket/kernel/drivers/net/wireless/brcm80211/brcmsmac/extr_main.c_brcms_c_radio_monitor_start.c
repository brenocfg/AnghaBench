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
struct brcms_c_info {int radio_monitor; int /*<<< orphan*/  radio_timer; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_PLLREQ_RADIO_MON ; 
 int /*<<< orphan*/  TIMER_INTERVAL_RADIOCHK ; 
 int /*<<< orphan*/  brcms_add_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_b_pllreq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_radio_monitor_start(struct brcms_c_info *wlc)
{
	/* Don't start the timer if HWRADIO feature is disabled */
	if (wlc->radio_monitor)
		return;

	wlc->radio_monitor = true;
	brcms_b_pllreq(wlc->hw, true, BRCMS_PLLREQ_RADIO_MON);
	brcms_add_timer(wlc->radio_timer, TIMER_INTERVAL_RADIOCHK, true);
}