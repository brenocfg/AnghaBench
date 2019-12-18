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
typedef  void* u8 ;
struct wl1251 {int dummy; } ;
struct acx_wake_up_condition {void* listen_interval; void* wake_up_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_WAKE_UP_CONDITIONS ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acx_wake_up_condition*) ; 
 struct acx_wake_up_condition* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_wake_up_condition*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_wake_up_conditions(struct wl1251 *wl, u8 wake_up_event,
				  u8 listen_interval)
{
	struct acx_wake_up_condition *wake_up;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx wake up conditions");

	wake_up = kzalloc(sizeof(*wake_up), GFP_KERNEL);
	if (!wake_up) {
		ret = -ENOMEM;
		goto out;
	}

	wake_up->wake_up_event = wake_up_event;
	wake_up->listen_interval = listen_interval;

	ret = wl1251_cmd_configure(wl, ACX_WAKE_UP_CONDITIONS,
				   wake_up, sizeof(*wake_up));
	if (ret < 0) {
		wl1251_warning("could not set wake up conditions: %d", ret);
		goto out;
	}

out:
	kfree(wake_up);
	return ret;
}