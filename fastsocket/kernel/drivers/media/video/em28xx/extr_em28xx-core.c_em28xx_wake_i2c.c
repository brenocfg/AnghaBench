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
struct em28xx {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  ctl_input; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmux; } ;

/* Variables and functions */
 TYPE_1__* INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  video ; 

void em28xx_wake_i2c(struct em28xx *dev)
{
	v4l2_device_call_all(&dev->v4l2_dev, 0, core,  reset, 0);
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_routing,
			INPUT(dev->ctl_input)->vmux, 0, 0);
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
}