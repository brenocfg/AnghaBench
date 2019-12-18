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
struct acx_event_mask {int high_event_mask; int /*<<< orphan*/  event_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_EVENT_MBOX_MASK ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_event_mask*) ; 
 struct acx_event_mask* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_event_mask*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_event_mbox_mask(struct wl1251 *wl, u32 event_mask)
{
	struct acx_event_mask *mask;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx event mbox mask");

	mask = kzalloc(sizeof(*mask), GFP_KERNEL);
	if (!mask) {
		ret = -ENOMEM;
		goto out;
	}

	/* high event mask is unused */
	mask->high_event_mask = 0xffffffff;

	mask->event_mask = event_mask;

	ret = wl1251_cmd_configure(wl, ACX_EVENT_MBOX_MASK,
				   mask, sizeof(*mask));
	if (ret < 0) {
		wl1251_warning("failed to set acx_event_mbox_mask: %d", ret);
		goto out;
	}

out:
	kfree(mask);
	return ret;
}