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
struct wl12xx_vif {int /*<<< orphan*/  flags; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLVIF_FLAG_RX_STREAMING_STARTED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_acx_ps_rx_streaming (struct wl1271*,struct wl12xx_vif*,int) ; 

__attribute__((used)) static int wl1271_set_rx_streaming(struct wl1271 *wl, struct wl12xx_vif *wlvif,
				   bool enable)
{
	int ret = 0;

	/* we should hold wl->mutex */
	ret = wl1271_acx_ps_rx_streaming(wl, wlvif, enable);
	if (ret < 0)
		goto out;

	if (enable)
		set_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvif->flags);
	else
		clear_bit(WLVIF_FLAG_RX_STREAMING_STARTED, &wlvif->flags);
out:
	return ret;
}