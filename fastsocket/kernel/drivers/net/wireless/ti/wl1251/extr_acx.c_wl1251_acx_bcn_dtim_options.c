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
struct wl1251 {int dummy; } ;
struct acx_beacon_broadcast {int /*<<< orphan*/  ps_poll_threshold; int /*<<< orphan*/  rx_broadcast_in_ps; int /*<<< orphan*/  broadcast_timeout; int /*<<< orphan*/  beacon_rx_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_BCN_DTIM_OPTIONS ; 
 int /*<<< orphan*/  BCN_RX_TIMEOUT_DEF_VALUE ; 
 int /*<<< orphan*/  BROADCAST_RX_TIMEOUT_DEF_VALUE ; 
 int /*<<< orphan*/  CONSECUTIVE_PS_POLL_FAILURE_DEF ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RX_BROADCAST_IN_PS_DEF_VALUE ; 
 int /*<<< orphan*/  kfree (struct acx_beacon_broadcast*) ; 
 struct acx_beacon_broadcast* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_beacon_broadcast*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_bcn_dtim_options(struct wl1251 *wl)
{
	struct acx_beacon_broadcast *bb;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx bcn dtim options");

	bb = kzalloc(sizeof(*bb), GFP_KERNEL);
	if (!bb) {
		ret = -ENOMEM;
		goto out;
	}

	bb->beacon_rx_timeout = BCN_RX_TIMEOUT_DEF_VALUE;
	bb->broadcast_timeout = BROADCAST_RX_TIMEOUT_DEF_VALUE;
	bb->rx_broadcast_in_ps = RX_BROADCAST_IN_PS_DEF_VALUE;
	bb->ps_poll_threshold = CONSECUTIVE_PS_POLL_FAILURE_DEF;

	ret = wl1251_cmd_configure(wl, ACX_BCN_DTIM_OPTIONS, bb, sizeof(*bb));
	if (ret < 0) {
		wl1251_warning("failed to set rx config: %d", ret);
		goto out;
	}

out:
	kfree(bb);
	return ret;
}