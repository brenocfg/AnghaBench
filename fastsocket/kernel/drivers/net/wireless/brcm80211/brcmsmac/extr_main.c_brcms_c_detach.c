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
typedef  scalar_t__ uint ;
struct brcms_c_info {int /*<<< orphan*/  cmi; } ;

/* Variables and functions */
 scalar_t__ brcms_b_detach (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_channel_mgr_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_detach_mfree (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_detach_module (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_radio_monitor_stop (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_timers_deinit (struct brcms_c_info*) ; 

uint brcms_c_detach(struct brcms_c_info *wlc)
{
	uint callbacks = 0;

	if (wlc == NULL)
		return 0;

	callbacks += brcms_b_detach(wlc);

	/* delete software timers */
	if (!brcms_c_radio_monitor_stop(wlc))
		callbacks++;

	brcms_c_channel_mgr_detach(wlc->cmi);

	brcms_c_timers_deinit(wlc);

	brcms_c_detach_module(wlc);

	brcms_c_detach_mfree(wlc);
	return callbacks;
}