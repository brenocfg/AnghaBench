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
struct TYPE_5__ {scalar_t__ streamState; } ;
struct TYPE_6__ {TYPE_2__ status; } ;
struct cam_data {TYPE_3__ params; int /*<<< orphan*/  raw_image; int /*<<< orphan*/  lowlevel_data; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* streamRead ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ STREAM_PAUSED ; 
 int /*<<< orphan*/  do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_stall(struct cam_data *cam)
{
	/* FIXME: Does this actually work? */
	LOG("Clearing stall\n");

	cam->ops->streamRead(cam->lowlevel_data, cam->raw_image, 0);
	do_command(cam, CPIA_COMMAND_GetCameraStatus,0,0,0,0);
	return cam->params.status.streamState != STREAM_PAUSED;
}