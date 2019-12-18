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
struct acx_slot {int slot_time; int /*<<< orphan*/  wone_index; } ;
typedef  enum acx_slot_type { ____Placeholder_acx_slot_type } acx_slot_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SLOT ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STATION_WONE_INDEX ; 
 int /*<<< orphan*/  kfree (struct acx_slot*) ; 
 struct acx_slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_slot*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_slot(struct wl1251 *wl, enum acx_slot_type slot_time)
{
	struct acx_slot *slot;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx slot");

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot) {
		ret = -ENOMEM;
		goto out;
	}

	slot->wone_index = STATION_WONE_INDEX;
	slot->slot_time = slot_time;

	ret = wl1251_cmd_configure(wl, ACX_SLOT, slot, sizeof(*slot));
	if (ret < 0) {
		wl1251_warning("failed to set slot time: %d", ret);
		goto out;
	}

out:
	kfree(slot);
	return ret;
}