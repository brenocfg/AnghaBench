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
struct TYPE_5__ {int x; int y; } ;
struct TYPE_4__ {int x; int y; } ;
struct pwc_device {scalar_t__ pixfmt; int image_mask; TYPE_2__ view_max; TYPE_1__ abs_max; } ;
struct TYPE_6__ {int x; int y; } ;

/* Variables and functions */
 int PSZ_MAX ; 
 int /*<<< orphan*/  PWC_DEBUG_SIZE (char*) ; 
 scalar_t__ V4L2_PIX_FMT_YUV420 ; 
 TYPE_3__* pwc_image_sizes ; 

int pwc_decode_size(struct pwc_device *pdev, int width, int height)
{
	int i, find;

	/* Make sure we don't go beyond our max size.
	   NB: we have different limits for RAW and normal modes. In case
	   you don't have the decompressor loaded or use RAW mode,
	   the maximum viewable size is smaller.
	*/
	if (pdev->pixfmt != V4L2_PIX_FMT_YUV420)
	{
		if (width > pdev->abs_max.x || height > pdev->abs_max.y)
		{
			PWC_DEBUG_SIZE("VIDEO_PALETTE_RAW: going beyond abs_max.\n");
			return -1;
		}
	}
	else
	{
		if (width > pdev->view_max.x || height > pdev->view_max.y)
		{
			PWC_DEBUG_SIZE("VIDEO_PALETTE_not RAW: going beyond view_max.\n");
			return -1;
		}
	}

	/* Find the largest size supported by the camera that fits into the
	   requested size.
	 */
	find = -1;
	for (i = 0; i < PSZ_MAX; i++) {
		if (pdev->image_mask & (1 << i)) {
			if (pwc_image_sizes[i].x <= width && pwc_image_sizes[i].y <= height)
				find = i;
		}
	}
	return find;
}