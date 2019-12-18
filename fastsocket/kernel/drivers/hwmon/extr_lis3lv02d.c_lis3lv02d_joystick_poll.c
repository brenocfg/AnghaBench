#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_polled_dev {int /*<<< orphan*/  input; } ;
struct TYPE_3__ {scalar_t__ zcalib; scalar_t__ ycalib; scalar_t__ xcalib; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  lis3lv02d_get_xyz (TYPE_1__*,int*,int*,int*) ; 

__attribute__((used)) static void lis3lv02d_joystick_poll(struct input_polled_dev *pidev)
{
	int x, y, z;

	lis3lv02d_get_xyz(&lis3_dev, &x, &y, &z);
	input_report_abs(pidev->input, ABS_X, x - lis3_dev.xcalib);
	input_report_abs(pidev->input, ABS_Y, y - lis3_dev.ycalib);
	input_report_abs(pidev->input, ABS_Z, z - lis3_dev.zcalib);
}