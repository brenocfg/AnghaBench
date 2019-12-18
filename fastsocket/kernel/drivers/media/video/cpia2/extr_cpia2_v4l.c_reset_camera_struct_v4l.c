#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_13__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  mains_frequency; int /*<<< orphan*/  flicker_mode_req; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {scalar_t__ contrast; scalar_t__ saturation; scalar_t__ brightness; } ;
struct TYPE_14__ {TYPE_6__ camera_state; TYPE_5__ flicker_control; TYPE_3__ roi; TYPE_2__ color_params; } ;
struct TYPE_11__ {scalar_t__ clipcount; scalar_t__ flags; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {int palette; int brightness; int colour; int contrast; } ;
struct camera_data {int /*<<< orphan*/  prio; int /*<<< orphan*/  pixelformat; TYPE_7__ params; int /*<<< orphan*/  num_frames; int /*<<< orphan*/  frame_size; TYPE_4__ vw; TYPE_1__ vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_JPEG ; 
 scalar_t__ VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  alternate ; 
 int /*<<< orphan*/  buffer_size ; 
 int /*<<< orphan*/  flicker_freq ; 
 int /*<<< orphan*/  flicker_mode ; 
 int /*<<< orphan*/  num_buffers ; 
 int /*<<< orphan*/  v4l2_prio_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_camera_struct_v4l(struct camera_data *cam)
{
	/***
	 * Fill in the v4l structures.  video_cap is filled in inside the VIDIOCCAP
	 * Ioctl.  Here, just do the window and picture stucts.
	 ***/
	cam->vp.palette = (u16) VIDEO_PALETTE_RGB24;	/* Is this right? */
	cam->vp.brightness = (u16) cam->params.color_params.brightness * 256;
	cam->vp.colour = (u16) cam->params.color_params.saturation * 256;
	cam->vp.contrast = (u16) cam->params.color_params.contrast * 256;

	cam->vw.x = 0;
	cam->vw.y = 0;
	cam->vw.width = cam->params.roi.width;
	cam->vw.height = cam->params.roi.height;
	cam->vw.flags = 0;
	cam->vw.clipcount = 0;

	cam->frame_size = buffer_size;
	cam->num_frames = num_buffers;

	/* FlickerModes */
	cam->params.flicker_control.flicker_mode_req = flicker_mode;
	cam->params.flicker_control.mains_frequency = flicker_freq;

	/* streamMode */
	cam->params.camera_state.stream_mode = alternate;

	cam->pixelformat = V4L2_PIX_FMT_JPEG;
	v4l2_prio_init(&cam->prio);
	return;
}