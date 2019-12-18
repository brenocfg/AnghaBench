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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9v011 {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 int mt9v011_try_mbus_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  set_res (struct v4l2_subdev*) ; 
 struct mt9v011* to_mt9v011 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v011_s_mbus_fmt(struct v4l2_subdev *sd, struct v4l2_mbus_framefmt *fmt)
{
	struct mt9v011 *core = to_mt9v011(sd);
	int rc;

	rc = mt9v011_try_mbus_fmt(sd, fmt);
	if (rc < 0)
		return -EINVAL;

	core->width = fmt->width;
	core->height = fmt->height;

	set_res(sd);

	return 0;
}