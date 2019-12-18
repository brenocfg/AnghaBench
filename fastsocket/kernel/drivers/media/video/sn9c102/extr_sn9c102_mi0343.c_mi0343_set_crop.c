#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct v4l2_rect {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_3__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_4__ {TYPE_1__ bounds; } ;
struct sn9c102_sensor {TYPE_2__ cropcap; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 struct sn9c102_sensor* sn9c102_get_sensor (struct sn9c102_device*) ; 
 scalar_t__ sn9c102_write_reg (struct sn9c102_device*,scalar_t__,int) ; 

__attribute__((used)) static int mi0343_set_crop(struct sn9c102_device* cam,
			    const struct v4l2_rect* rect)
{
	struct sn9c102_sensor* s = sn9c102_get_sensor(cam);
	int err = 0;
	u8 h_start = (u8)(rect->left - s->cropcap.bounds.left) + 0,
	   v_start = (u8)(rect->top - s->cropcap.bounds.top) + 2;

	err += sn9c102_write_reg(cam, h_start, 0x12);
	err += sn9c102_write_reg(cam, v_start, 0x13);

	return err;
}