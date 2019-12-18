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
struct TYPE_3__ {int width; int height; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct cx18_open_id {scalar_t__ type; struct cx18* cx; } ;
struct cx18 {scalar_t__ is_50hz; } ;

/* Variables and functions */
 scalar_t__ CX18_ENC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  cx18_g_fmt_vid_cap (struct file*,void*,struct v4l2_format*) ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int cx18_try_fmt_vid_cap(struct file *file, void *fh,
				struct v4l2_format *fmt)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	int w = fmt->fmt.pix.width;
	int h = fmt->fmt.pix.height;
	int min_h = 2;

	w = min(w, 720);
	w = max(w, 2);
	if (id->type == CX18_ENC_STREAM_TYPE_YUV) {
		/* YUV height must be a multiple of 32 */
		h &= ~0x1f;
		min_h = 32;
	}
	h = min(h, cx->is_50hz ? 576 : 480);
	h = max(h, min_h);

	cx18_g_fmt_vid_cap(file, fh, fmt);
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	return 0;
}