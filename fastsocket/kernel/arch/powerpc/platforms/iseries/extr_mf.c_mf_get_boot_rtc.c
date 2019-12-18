#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ce_msg; } ;
struct ce_msg_comp_data {int busy; TYPE_1__ ce_msg; int /*<<< orphan*/  rc; struct ce_msg_comp_data* token; int /*<<< orphan*/ * handler; } ;
struct boot_rtc_time_data {int busy; TYPE_1__ ce_msg; int /*<<< orphan*/  rc; struct boot_rtc_time_data* token; int /*<<< orphan*/ * handler; } ;
typedef  int /*<<< orphan*/  rtc_data ;
typedef  int /*<<< orphan*/  ce_complete ;

/* Variables and functions */
 int /*<<< orphan*/  get_boot_rtc_time_complete ; 
 scalar_t__ hvlpevent_is_pending () ; 
 int /*<<< orphan*/  memset (struct ce_msg_comp_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_hvlpevents () ; 
 int rtc_set_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_time*) ; 
 int signal_ce_msg_simple (int,struct ce_msg_comp_data*) ; 

__attribute__((used)) static int mf_get_boot_rtc(struct rtc_time *tm)
{
	struct ce_msg_comp_data ce_complete;
	struct boot_rtc_time_data rtc_data;
	int rc;

	memset(&ce_complete, 0, sizeof(ce_complete));
	memset(&rtc_data, 0, sizeof(rtc_data));
	rtc_data.busy = 1;
	ce_complete.handler = &get_boot_rtc_time_complete;
	ce_complete.token = &rtc_data;
	rc = signal_ce_msg_simple(0x40, &ce_complete);
	if (rc)
		return rc;
	/* We need to poll here as we are not yet taking interrupts */
	while (rtc_data.busy) {
		if (hvlpevent_is_pending())
			process_hvlpevents();
	}
	return rtc_set_tm(rtc_data.rc, rtc_data.ce_msg.ce_msg, tm);
}