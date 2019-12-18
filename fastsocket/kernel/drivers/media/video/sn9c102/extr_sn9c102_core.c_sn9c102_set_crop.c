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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_rect {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_3__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_4__ {TYPE_1__ bounds; } ;
struct sn9c102_sensor {TYPE_2__ cropcap; } ;
struct sn9c102_device {struct sn9c102_sensor sensor; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PDBGG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sn9c102_write_reg (struct sn9c102_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sn9c102_set_crop(struct sn9c102_device* cam, struct v4l2_rect* rect)
{
	struct sn9c102_sensor* s = &cam->sensor;
	u8 h_start = (u8)(rect->left - s->cropcap.bounds.left),
	   v_start = (u8)(rect->top - s->cropcap.bounds.top),
	   h_size = (u8)(rect->width / 16),
	   v_size = (u8)(rect->height / 16);
	int err = 0;

	err += sn9c102_write_reg(cam, h_start, 0x12);
	err += sn9c102_write_reg(cam, v_start, 0x13);
	err += sn9c102_write_reg(cam, h_size, 0x15);
	err += sn9c102_write_reg(cam, v_size, 0x16);
	if (err)
		return -EIO;

	PDBGG("h_start, v_start, h_size, v_size, ho_size, vo_size "
	      "%u %u %u %u", h_start, v_start, h_size, v_size);

	return 0;
}