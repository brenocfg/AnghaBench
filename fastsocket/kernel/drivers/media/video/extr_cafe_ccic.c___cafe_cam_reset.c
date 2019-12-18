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
struct cafe_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  reset ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cafe_cam_reset(struct cafe_camera *cam)
{
	return sensor_call(cam, core, reset, 0);
}