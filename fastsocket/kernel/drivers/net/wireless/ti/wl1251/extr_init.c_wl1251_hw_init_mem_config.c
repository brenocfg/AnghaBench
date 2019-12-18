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
struct wl1251_acx_mem_map {int dummy; } ;
struct wl1251 {int /*<<< orphan*/ * target_mem_map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_acx_mem_cfg (struct wl1251*) ; 
 int wl1251_acx_mem_map (struct wl1251*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 

int wl1251_hw_init_mem_config(struct wl1251 *wl)
{
	int ret;

	ret = wl1251_acx_mem_cfg(wl);
	if (ret < 0)
		return ret;

	wl->target_mem_map = kzalloc(sizeof(struct wl1251_acx_mem_map),
					  GFP_KERNEL);
	if (!wl->target_mem_map) {
		wl1251_error("couldn't allocate target memory map");
		return -ENOMEM;
	}

	/* we now ask for the firmware built memory map */
	ret = wl1251_acx_mem_map(wl, wl->target_mem_map,
				 sizeof(struct wl1251_acx_mem_map));
	if (ret < 0) {
		wl1251_error("couldn't retrieve firmware memory map");
		kfree(wl->target_mem_map);
		wl->target_mem_map = NULL;
		return ret;
	}

	return 0;
}