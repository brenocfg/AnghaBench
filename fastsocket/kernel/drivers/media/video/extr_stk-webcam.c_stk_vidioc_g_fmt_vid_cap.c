#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {int width; int height; scalar_t__ pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_6__ {scalar_t__ mode; scalar_t__ palette; } ;
struct stk_camera {TYPE_2__ vsettings; } ;
struct file {int dummy; } ;
struct TYPE_7__ {scalar_t__ m; int w; int h; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  STK_ERROR (char*) ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_SBGGR8 ; 
 TYPE_3__* stk_sizes ; 

__attribute__((used)) static int stk_vidioc_g_fmt_vid_cap(struct file *filp,
		void *priv, struct v4l2_format *f)
{
	struct v4l2_pix_format *pix_format = &f->fmt.pix;
	struct stk_camera *dev = priv;
	int i;

	for (i = 0; i < ARRAY_SIZE(stk_sizes)
			&& stk_sizes[i].m != dev->vsettings.mode;
		i++);
	if (i == ARRAY_SIZE(stk_sizes)) {
		STK_ERROR("ERROR: mode invalid\n");
		return -EINVAL;
	}
	pix_format->width = stk_sizes[i].w;
	pix_format->height = stk_sizes[i].h;
	pix_format->field = V4L2_FIELD_NONE;
	pix_format->colorspace = V4L2_COLORSPACE_SRGB;
	pix_format->pixelformat = dev->vsettings.palette;
	if (dev->vsettings.palette == V4L2_PIX_FMT_SBGGR8)
		pix_format->bytesperline = pix_format->width;
	else
		pix_format->bytesperline = 2 * pix_format->width;
	pix_format->sizeimage = pix_format->bytesperline
				* pix_format->height;
	return 0;
}