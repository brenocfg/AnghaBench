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
struct TYPE_3__ {float x; float y; float a; float b; float roll; float pitch; float yaw; } ;
typedef  TYPE_1__ ccv_decimal_pose_t ;

/* Variables and functions */

__attribute__((used)) inline static ccv_decimal_pose_t ccv_decimal_pose(float x, float y, float a, float b, float roll, float pitch, float yaw)
{
	ccv_decimal_pose_t pose;
	pose.x = x;
	pose.y = y;
	pose.a = a;
	pose.b = b;
	pose.roll = roll;
	pose.pitch = pitch;
	pose.yaw = yaw;
	return pose;
}