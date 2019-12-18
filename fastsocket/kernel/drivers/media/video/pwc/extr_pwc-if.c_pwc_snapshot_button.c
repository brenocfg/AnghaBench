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
struct pwc_device {int snapshot_button_status; scalar_t__ button_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  PWC_TRACE (char*) ; 
 int /*<<< orphan*/  input_report_key (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (scalar_t__) ; 

__attribute__((used)) static void pwc_snapshot_button(struct pwc_device *pdev, int down)
{
	if (down) {
		PWC_TRACE("Snapshot button pressed.\n");
		pdev->snapshot_button_status = 1;
	} else {
		PWC_TRACE("Snapshot button released.\n");
	}

#ifdef CONFIG_USB_PWC_INPUT_EVDEV
	if (pdev->button_dev) {
		input_report_key(pdev->button_dev, KEY_CAMERA, down);
		input_sync(pdev->button_dev);
	}
#endif
}