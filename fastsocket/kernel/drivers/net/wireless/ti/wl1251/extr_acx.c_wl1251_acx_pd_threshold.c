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
struct acx_packet_detection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_PD_THRESHOLD ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_packet_detection*) ; 
 struct acx_packet_detection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_packet_detection*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_pd_threshold(struct wl1251 *wl)
{
	struct acx_packet_detection *pd;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx data pd threshold");

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd) {
		ret = -ENOMEM;
		goto out;
	}

	/* FIXME: threshold value not set */

	ret = wl1251_cmd_configure(wl, ACX_PD_THRESHOLD, pd, sizeof(*pd));
	if (ret < 0) {
		wl1251_warning("failed to set pd threshold: %d", ret);
		goto out;
	}

out:
	kfree(pd);
	return ret;
}