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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl1271_ps_elp_sleep (struct wl1271*) ; 
 int wl1271_ps_elp_wakeup (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

__attribute__((used)) static void chip_op_handler(struct wl1271 *wl, unsigned long value,
			    void *arg)
{
	int ret;
	int (*chip_op) (struct wl1271 *wl);

	if (!arg) {
		wl1271_warning("debugfs chip_op_handler with no callback");
		return;
	}

	ret = wl1271_ps_elp_wakeup(wl);
	if (ret < 0)
		return;

	chip_op = arg;
	chip_op(wl);

	wl1271_ps_elp_sleep(wl);
}