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
struct TYPE_3__ {int depth; int channels; int /*<<< orphan*/  name; int /*<<< orphan*/  type; scalar_t__ channel; scalar_t__ tuners; scalar_t__ flags; int /*<<< orphan*/  maxheight; int /*<<< orphan*/  maxwidth; int /*<<< orphan*/  minheight; int /*<<< orphan*/  minwidth; scalar_t__ audios; int /*<<< orphan*/  palette; int /*<<< orphan*/  whiteness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; int /*<<< orphan*/  hue; int /*<<< orphan*/  colour; } ;
struct uvd {TYPE_1__ vchan; TYPE_1__ vcap; TYPE_1__ vpic; TYPE_1__ vpic_old; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 size_t SIZE_160X120 ; 
 size_t SIZE_320X240 ; 
 int /*<<< orphan*/  VIDEO_PALETTE_RGB24 ; 
 int /*<<< orphan*/  VIDEO_TYPE_CAMERA ; 
 int /*<<< orphan*/  VID_TYPE_CAPTURE ; 
 int /*<<< orphan*/  brightness ; 
 TYPE_2__* camera_sizes ; 
 int /*<<< orphan*/  colour ; 
 int /*<<< orphan*/  contrast ; 
 int /*<<< orphan*/  hue ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  qcm_sensor_init (struct uvd*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  whiteness ; 

__attribute__((used)) static int qcm_configure_video(struct uvd *uvd)
{
	int ret;
	memset(&uvd->vpic, 0, sizeof(uvd->vpic));
	memset(&uvd->vpic_old, 0x55, sizeof(uvd->vpic_old));

	uvd->vpic.colour = colour;
	uvd->vpic.hue = hue;
	uvd->vpic.brightness = brightness;
	uvd->vpic.contrast = contrast;
	uvd->vpic.whiteness = whiteness;
	uvd->vpic.depth = 24;
	uvd->vpic.palette = VIDEO_PALETTE_RGB24;

	memset(&uvd->vcap, 0, sizeof(uvd->vcap));
	strcpy(uvd->vcap.name, "QCM USB Camera");
	uvd->vcap.type = VID_TYPE_CAPTURE;
	uvd->vcap.channels = 1;
	uvd->vcap.audios = 0;

	uvd->vcap.minwidth = camera_sizes[SIZE_160X120].width;
	uvd->vcap.minheight = camera_sizes[SIZE_160X120].height;
	uvd->vcap.maxwidth = camera_sizes[SIZE_320X240].width;
	uvd->vcap.maxheight = camera_sizes[SIZE_320X240].height;

	memset(&uvd->vchan, 0, sizeof(uvd->vchan));
	uvd->vchan.flags = 0 ;
	uvd->vchan.tuners = 0;
	uvd->vchan.channel = 0;
	uvd->vchan.type = VIDEO_TYPE_CAMERA;
	strcpy(uvd->vchan.name, "Camera");

	CHECK_RET(ret, qcm_sensor_init(uvd));
	return 0;
}