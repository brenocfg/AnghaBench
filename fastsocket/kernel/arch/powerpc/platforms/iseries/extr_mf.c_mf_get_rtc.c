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
struct TYPE_2__ {int /*<<< orphan*/  ce_msg; } ;
struct rtc_time_data {TYPE_1__ ce_msg; int /*<<< orphan*/  rc; int /*<<< orphan*/  com; struct rtc_time_data* token; int /*<<< orphan*/ * handler; } ;
struct rtc_time {int dummy; } ;
struct ce_msg_comp_data {TYPE_1__ ce_msg; int /*<<< orphan*/  rc; int /*<<< orphan*/  com; struct ce_msg_comp_data* token; int /*<<< orphan*/ * handler; } ;
typedef  int /*<<< orphan*/  rtc_data ;
typedef  int /*<<< orphan*/  ce_complete ;

/* Variables and functions */
 int /*<<< orphan*/  get_rtc_time_complete ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rtc_time_data*,int /*<<< orphan*/ ,int) ; 
 int rtc_set_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_time*) ; 
 int signal_ce_msg_simple (int,struct rtc_time_data*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mf_get_rtc(struct rtc_time *tm)
{
	struct ce_msg_comp_data ce_complete;
	struct rtc_time_data rtc_data;
	int rc;

	memset(&ce_complete, 0, sizeof(ce_complete));
	memset(&rtc_data, 0, sizeof(rtc_data));
	init_completion(&rtc_data.com);
	ce_complete.handler = &get_rtc_time_complete;
	ce_complete.token = &rtc_data;
	rc = signal_ce_msg_simple(0x40, &ce_complete);
	if (rc)
		return rc;
	wait_for_completion(&rtc_data.com);
	return rtc_set_tm(rtc_data.rc, rtc_data.ce_msg.ce_msg, tm);
}