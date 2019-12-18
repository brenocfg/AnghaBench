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
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_querymenu {int dummy; } ;

/* Variables and functions */
 int v4l2_querymenu (int /*<<< orphan*/ ,struct v4l2_querymenu*) ; 

int v4l2_subdev_querymenu(struct v4l2_subdev *sd, struct v4l2_querymenu *qm)
{
	return v4l2_querymenu(sd->ctrl_handler, qm);
}