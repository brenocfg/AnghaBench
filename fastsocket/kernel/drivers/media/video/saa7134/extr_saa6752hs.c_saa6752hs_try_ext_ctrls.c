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
struct v4l2_ext_controls {int dummy; } ;

/* Variables and functions */
 int saa6752hs_do_ext_ctrls (struct v4l2_subdev*,struct v4l2_ext_controls*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa6752hs_try_ext_ctrls(struct v4l2_subdev *sd, struct v4l2_ext_controls *ctrls)
{
	return saa6752hs_do_ext_ctrls(sd, ctrls, 0);
}