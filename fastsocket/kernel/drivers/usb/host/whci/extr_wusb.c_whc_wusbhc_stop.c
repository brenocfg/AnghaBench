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
typedef  int u32 ;
struct wusbhc {int dummy; } ;
struct whc {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WUSBGENCMDSTS_CHAN_STOP ; 
 scalar_t__ WUSBTIME ; 
 int WUSBTIME_CHANNEL_TIME_MASK ; 
 int /*<<< orphan*/  asl_stop (struct whc*) ; 
 int le_readl (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pzl_stop (struct whc*) ; 
 int whc_do_gencmd (struct whc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

void whc_wusbhc_stop(struct wusbhc *wusbhc, int delay)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);
	u32 stop_time, now_time;
	int ret;

	pzl_stop(whc);
	asl_stop(whc);

	now_time = le_readl(whc->base + WUSBTIME) & WUSBTIME_CHANNEL_TIME_MASK;
	stop_time = (now_time + ((delay * 8) << 7)) & 0x00ffffff;
	ret = whc_do_gencmd(whc, WUSBGENCMDSTS_CHAN_STOP, stop_time, NULL, 0);
	if (ret == 0)
		msleep(delay);
}