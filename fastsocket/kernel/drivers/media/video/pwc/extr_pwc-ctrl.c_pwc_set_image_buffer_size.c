#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int x; int y; } ;
struct TYPE_6__ {int size; int x; int y; } ;
struct TYPE_5__ {int x; int y; } ;
struct pwc_device {int pixfmt; unsigned char* image_data; TYPE_4__ view; TYPE_3__* images; TYPE_2__ image; TYPE_1__ offset; } ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_U ; 
 int /*<<< orphan*/  BLACK_V ; 
 int /*<<< orphan*/  BLACK_Y ; 
#define  V4L2_PIX_FMT_PWC1 130 
#define  V4L2_PIX_FMT_PWC2 129 
#define  V4L2_PIX_FMT_YUV420 128 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int pwc_mbufs ; 

__attribute__((used)) static void pwc_set_image_buffer_size(struct pwc_device *pdev)
{
	int i, factor = 0;

	/* for V4L2_PIX_FMT_YUV420 */
	switch (pdev->pixfmt) {
	case V4L2_PIX_FMT_YUV420:
		factor = 6;
		break;
	case V4L2_PIX_FMT_PWC1:
	case V4L2_PIX_FMT_PWC2:
		factor = 6; /* can be uncompressed YUV420P */
		break;
	}

	/* Set sizes in bytes */
	pdev->image.size = pdev->image.x * pdev->image.y * factor / 4;
	pdev->view.size  = pdev->view.x  * pdev->view.y  * factor / 4;

	/* Align offset, or you'll get some very weird results in
	   YUV420 mode... x must be multiple of 4 (to get the Y's in
	   place), and y even (or you'll mixup U & V). This is less of a
	   problem for YUV420P.
	 */
	pdev->offset.x = ((pdev->view.x - pdev->image.x) / 2) & 0xFFFC;
	pdev->offset.y = ((pdev->view.y - pdev->image.y) / 2) & 0xFFFE;

	/* Fill buffers with black colors */
	for (i = 0; i < pwc_mbufs; i++) {
		unsigned char *p = pdev->image_data + pdev->images[i].offset;
		memset(p, BLACK_Y, pdev->view.x * pdev->view.y);
		p += pdev->view.x * pdev->view.y;
		memset(p, BLACK_U, pdev->view.x * pdev->view.y/4);
		p += pdev->view.x * pdev->view.y/4;
		memset(p, BLACK_V, pdev->view.x * pdev->view.y/4);
	}
}