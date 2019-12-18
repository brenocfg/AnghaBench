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
struct v4l2_control {int dummy; } ;
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct cx8800_fh {TYPE_1__* dev; } ;
struct TYPE_2__ {struct cx88_core* core; } ;

/* Variables and functions */
 int cx88_get_control (struct cx88_core*,struct v4l2_control*) ; 

__attribute__((used)) static int vidioc_g_ctrl (struct file *file, void *priv,
				struct v4l2_control *ctl)
{
	struct cx88_core  *core = ((struct cx8800_fh *)priv)->dev->core;
	return
		cx88_get_control(core,ctl);
}