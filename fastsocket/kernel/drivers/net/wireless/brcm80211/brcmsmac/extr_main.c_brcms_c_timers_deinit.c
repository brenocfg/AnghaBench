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
struct brcms_c_info {int /*<<< orphan*/ * radio_timer; int /*<<< orphan*/ * wdtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_free_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcms_c_timers_deinit(struct brcms_c_info *wlc)
{
	/* free timer state */
	if (wlc->wdtimer) {
		brcms_free_timer(wlc->wdtimer);
		wlc->wdtimer = NULL;
	}
	if (wlc->radio_timer) {
		brcms_free_timer(wlc->radio_timer);
		wlc->radio_timer = NULL;
	}
}