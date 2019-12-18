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
struct acx_energy_detection {scalar_t__ tx_energy_detection; int /*<<< orphan*/  rx_cca_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_CCA_THRESHOLD ; 
 int /*<<< orphan*/  CCA_THRSH_DISABLE_ENERGY_D ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_energy_detection*) ; 
 struct acx_energy_detection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_energy_detection*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_cca_threshold(struct wl1251 *wl)
{
	struct acx_energy_detection *detection;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx cca threshold");

	detection = kzalloc(sizeof(*detection), GFP_KERNEL);
	if (!detection) {
		ret = -ENOMEM;
		goto out;
	}

	detection->rx_cca_threshold = CCA_THRSH_DISABLE_ENERGY_D;
	detection->tx_energy_detection = 0;

	ret = wl1251_cmd_configure(wl, ACX_CCA_THRESHOLD,
				   detection, sizeof(*detection));
	if (ret < 0)
		wl1251_warning("failed to set cca threshold: %d", ret);

out:
	kfree(detection);
	return ret;
}