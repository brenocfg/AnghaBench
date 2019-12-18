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
struct TYPE_3__ {int /*<<< orphan*/  zcalib; int /*<<< orphan*/  ycalib; int /*<<< orphan*/  xcalib; } ;

/* Variables and functions */
 TYPE_1__ lis3_dev ; 
 int /*<<< orphan*/  lis3lv02d_get_xyz (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void lis3lv02d_calibrate_joystick(void)
{
	lis3lv02d_get_xyz(&lis3_dev,
		&lis3_dev.xcalib, &lis3_dev.ycalib, &lis3_dev.zcalib);
}