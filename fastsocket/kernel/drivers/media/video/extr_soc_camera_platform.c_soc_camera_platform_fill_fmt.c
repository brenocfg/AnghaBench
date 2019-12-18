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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct soc_camera_platform_info {TYPE_1__ format; } ;

/* Variables and functions */
 struct soc_camera_platform_info* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int soc_camera_platform_fill_fmt(struct v4l2_subdev *sd,
					struct v4l2_mbus_framefmt *mf)
{
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(sd);

	mf->width	= p->format.width;
	mf->height	= p->format.height;
	mf->code	= p->format.code;
	mf->colorspace	= p->format.colorspace;
	mf->field	= p->format.field;

	return 0;
}