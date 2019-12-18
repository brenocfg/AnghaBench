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
typedef  int /*<<< orphan*/  u32 ;
struct wl1251 {int dummy; } ;
struct acx_rx_msdu_lifetime {int /*<<< orphan*/  lifetime; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_ACX ; 
 int /*<<< orphan*/  DOT11_RX_MSDU_LIFE_TIME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_rx_msdu_lifetime*) ; 
 struct acx_rx_msdu_lifetime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_rx_msdu_lifetime*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_rx_msdu_life_time(struct wl1251 *wl, u32 life_time)
{
	struct acx_rx_msdu_lifetime *acx;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx rx msdu life time");

	acx = kzalloc(sizeof(*acx), GFP_KERNEL);
	if (!acx) {
		ret = -ENOMEM;
		goto out;
	}

	acx->lifetime = life_time;
	ret = wl1251_cmd_configure(wl, DOT11_RX_MSDU_LIFE_TIME,
				   acx, sizeof(*acx));
	if (ret < 0) {
		wl1251_warning("failed to set rx msdu life time: %d", ret);
		goto out;
	}

out:
	kfree(acx);
	return ret;
}