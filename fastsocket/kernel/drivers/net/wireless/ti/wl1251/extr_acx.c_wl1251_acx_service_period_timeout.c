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
struct acx_rx_timeout {int /*<<< orphan*/  upsd_timeout; int /*<<< orphan*/  ps_poll_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SERVICE_PERIOD_TIMEOUT ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RX_TIMEOUT_PS_POLL_DEF ; 
 int /*<<< orphan*/  RX_TIMEOUT_UPSD_DEF ; 
 int /*<<< orphan*/  kfree (struct acx_rx_timeout*) ; 
 struct acx_rx_timeout* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_rx_timeout*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_service_period_timeout(struct wl1251 *wl)
{
	struct acx_rx_timeout *rx_timeout;
	int ret;

	rx_timeout = kzalloc(sizeof(*rx_timeout), GFP_KERNEL);
	if (!rx_timeout) {
		ret = -ENOMEM;
		goto out;
	}

	wl1251_debug(DEBUG_ACX, "acx service period timeout");

	rx_timeout->ps_poll_timeout = RX_TIMEOUT_PS_POLL_DEF;
	rx_timeout->upsd_timeout = RX_TIMEOUT_UPSD_DEF;

	ret = wl1251_cmd_configure(wl, ACX_SERVICE_PERIOD_TIMEOUT,
				   rx_timeout, sizeof(*rx_timeout));
	if (ret < 0) {
		wl1251_warning("failed to set service period timeout: %d",
			       ret);
		goto out;
	}

out:
	kfree(rx_timeout);
	return ret;
}