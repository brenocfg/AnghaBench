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
typedef  void* u32 ;
struct wl1251 {int dummy; } ;
struct acx_rx_config {void* filter_options; void* config_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_RX_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_rx_config*) ; 
 struct acx_rx_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_rx_config*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_rx_config(struct wl1251 *wl, u32 config, u32 filter)
{
	struct acx_rx_config *rx_config;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx rx config");

	rx_config = kzalloc(sizeof(*rx_config), GFP_KERNEL);
	if (!rx_config) {
		ret = -ENOMEM;
		goto out;
	}

	rx_config->config_options = config;
	rx_config->filter_options = filter;

	ret = wl1251_cmd_configure(wl, ACX_RX_CFG,
				   rx_config, sizeof(*rx_config));
	if (ret < 0) {
		wl1251_warning("failed to set rx config: %d", ret);
		goto out;
	}

out:
	kfree(rx_config);
	return ret;
}