#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wacom_wac {TYPE_1__* features; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ device_type; int /*<<< orphan*/  y_phy; int /*<<< orphan*/  x_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
 scalar_t__ BTN_TOOL_FINGER ; 
 scalar_t__ BTN_TOOL_PEN ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void input_dev_tpc(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	if (wacom_wac->features->device_type == BTN_TOOL_FINGER ||
	    wacom_wac->features->device_type == BTN_TOOL_PEN) {
		input_set_abs_params(input_dev, ABS_RX, 0, wacom_wac->features->x_phy, 0, 0);
		input_set_abs_params(input_dev, ABS_RY, 0, wacom_wac->features->y_phy, 0, 0);
	}
}