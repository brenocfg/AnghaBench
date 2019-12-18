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
struct TYPE_3__ {int x; int y; } ;
struct pwc_device {scalar_t__ frame_trailer_size; scalar_t__ frame_header_size; scalar_t__ frame_size; scalar_t__ frame_total_size; TYPE_1__ view; int /*<<< orphan*/  type; int /*<<< orphan*/  pixfmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVICE_USE_CODEC3 (int /*<<< orphan*/ ) ; 
 int ERANGE ; 
 int /*<<< orphan*/  PWC_DEBUG_FLOW (char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWC_DEBUG_MODULE (char*) ; 
 int /*<<< orphan*/  PWC_DEBUG_SIZE (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWC_ERROR (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PWC_TRACE (char*,int) ; 
 int pwc_decode_size (struct pwc_device*,int,int) ; 
 TYPE_2__* pwc_image_sizes ; 
 int /*<<< orphan*/  pwc_set_image_buffer_size (struct pwc_device*) ; 
 int set_video_mode_Kiara (struct pwc_device*,int,int,int,int) ; 
 int set_video_mode_Nala (struct pwc_device*,int,int) ; 
 int set_video_mode_Timon (struct pwc_device*,int,int,int,int) ; 
 int /*<<< orphan*/ * size2name ; 

int pwc_set_video_mode(struct pwc_device *pdev, int width, int height, int frames, int compression, int snapshot)
{
	int ret, size;

	PWC_DEBUG_FLOW("set_video_mode(%dx%d @ %d, pixfmt %08x).\n", width, height, frames, pdev->pixfmt);
	size = pwc_decode_size(pdev, width, height);
	if (size < 0) {
		PWC_DEBUG_MODULE("Could not find suitable size.\n");
		return -ERANGE;
	}
	PWC_TRACE("decode_size = %d.\n", size);

	if (DEVICE_USE_CODEC1(pdev->type)) {
		ret = set_video_mode_Nala(pdev, size, frames);

	} else if (DEVICE_USE_CODEC3(pdev->type)) {
		ret = set_video_mode_Kiara(pdev, size, frames, compression, snapshot);

	} else {
		ret = set_video_mode_Timon(pdev, size, frames, compression, snapshot);
	}
	if (ret < 0) {
		PWC_ERROR("Failed to set video mode %s@%d fps; return code = %d\n", size2name[size], frames, ret);
		return ret;
	}
	pdev->view.x = width;
	pdev->view.y = height;
	pdev->frame_total_size = pdev->frame_size + pdev->frame_header_size + pdev->frame_trailer_size;
	pwc_set_image_buffer_size(pdev);
	PWC_DEBUG_SIZE("Set viewport to %dx%d, image size is %dx%d.\n", width, height, pwc_image_sizes[size].x, pwc_image_sizes[size].y);
	return 0;
}