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
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct tcm825x_sensor {int /*<<< orphan*/  pix; TYPE_1__* platform_data; } ;
struct TYPE_2__ {int (* needs_reset ) (struct v4l2_int_device*,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct v4l2_int_device*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_g_needs_reset(struct v4l2_int_device *s, void *buf)
{
	struct tcm825x_sensor *sensor = s->priv;

	return sensor->platform_data->needs_reset(s, buf, &sensor->pix);
}