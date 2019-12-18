#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl12xx_vif {int /*<<< orphan*/  rx_streaming_timer; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int interval; scalar_t__ always; } ;
struct TYPE_4__ {TYPE_1__ rx_streaming; } ;
struct wl1271 {int /*<<< orphan*/  flags; TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_SOFT_GEMINI ; 
 int /*<<< orphan*/  WLVIF_FLAG_RX_STREAMING_STARTED ; 
 int /*<<< orphan*/  WLVIF_FLAG_STA_ASSOCIATED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_set_rx_streaming (struct wl1271*,struct wl12xx_vif*,int) ; 

int wl1271_recalc_rx_streaming(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	int ret = 0;
	int period = wl->conf.rx_streaming.interval;

	/* don't reconfigure if rx_streaming is disabled */
	if (!test_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvif->flags))
		goto out;

	/* reconfigure/disable according to new streaming_period */
	if (period &&
	    test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvif->flags) &&
	    (wl->conf.rx_streaming.always ||
	     test_bit(WL1271_FLAG_SOFT_GEMINI, &wl->flags)))
		ret = wl1271_set_rx_streaming(wl, wlvif, true);
	else {
		ret = wl1271_set_rx_streaming(wl, wlvif, false);
		/* don't cancel_work_sync since we might deadlock */
		del_timer_sync(&wlvif->rx_streaming_timer);
	}
out:
	return ret;
}