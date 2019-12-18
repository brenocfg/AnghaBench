#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_5__ {TYPE_1__ bounds; } ;
struct et61x251_sensor {TYPE_3__ active_pixel; TYPE_2__ cropcap; } ;
struct et61x251_device {struct et61x251_sensor sensor; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PDBGG (char*,int,int,int,int) ; 
 scalar_t__ et61x251_write_reg (struct et61x251_device*,int,int) ; 

__attribute__((used)) static int
et61x251_set_crop(struct et61x251_device* cam, struct v4l2_rect* rect)
{
	struct et61x251_sensor* s = &cam->sensor;
	u16 fmw_sx = (u16)(rect->left - s->cropcap.bounds.left +
			   s->active_pixel.left),
	    fmw_sy = (u16)(rect->top - s->cropcap.bounds.top +
			   s->active_pixel.top),
	    fmw_length = (u16)(rect->width),
	    fmw_height = (u16)(rect->height);
	int err = 0;

	err += et61x251_write_reg(cam, fmw_sx & 0xff, 0x69);
	err += et61x251_write_reg(cam, fmw_sy & 0xff, 0x6a);
	err += et61x251_write_reg(cam, fmw_length & 0xff, 0x6b);
	err += et61x251_write_reg(cam, fmw_height & 0xff, 0x6c);
	err += et61x251_write_reg(cam, (fmw_sx >> 8) | ((fmw_sy & 0x300) >> 6)
				       | ((fmw_length & 0x300) >> 4)
				       | ((fmw_height & 0x300) >> 2), 0x6d);
	if (err)
		return -EIO;

	PDBGG("fmw_sx, fmw_sy, fmw_length, fmw_height: %u %u %u %u",
	      fmw_sx, fmw_sy, fmw_length, fmw_height);

	return 0;
}