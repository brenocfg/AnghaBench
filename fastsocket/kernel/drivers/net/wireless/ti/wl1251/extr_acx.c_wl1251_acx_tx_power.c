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
struct acx_current_tx_power {int current_tx_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_CUR_TX_PWR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_current_tx_power*) ; 
 struct acx_current_tx_power* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_current_tx_power*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_tx_power(struct wl1251 *wl, int power)
{
	struct acx_current_tx_power *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx dot11_cur_tx_pwr");

	if (power < 0 || power > 25)
		return -EINVAL;

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->current_tx_power = power * 10;

	ret = wl1251_cmd_configure(wl, DOT11_CUR_TX_PWR, acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("configure of tx power failed: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}