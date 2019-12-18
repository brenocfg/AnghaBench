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
struct TYPE_3__ {int field; void* height; void* width; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct ivtv_open_id {scalar_t__ type; } ;
struct file {int dummy; } ;
typedef  void* s32 ;

/* Variables and functions */
 scalar_t__ IVTV_DEC_STREAM_TYPE_YUV ; 
 int ivtv_g_fmt_vid_out (struct file*,void*,struct v4l2_format*) ; 
 void* max (void*,int) ; 
 void* min (void*,int) ; 

__attribute__((used)) static int ivtv_try_fmt_vid_out(struct file *file, void *fh, struct v4l2_format *fmt)
{
	struct ivtv_open_id *id = fh;
	s32 w = fmt->fmt.pix.width;
	s32 h = fmt->fmt.pix.height;
	int field = fmt->fmt.pix.field;
	int ret = ivtv_g_fmt_vid_out(file, fh, fmt);

	w = min(w, 720);
	w = max(w, 2);
	/* Why can the height be 576 even when the output is NTSC?

	   Internally the buffers of the PVR350 are always set to 720x576. The
	   decoded video frame will always be placed in the top left corner of
	   this buffer. For any video which is not 720x576, the buffer will
	   then be cropped to remove the unused right and lower areas, with
	   the remaining image being scaled by the hardware to fit the display
	   area. The video can be scaled both up and down, so a 720x480 video
	   can be displayed full-screen on PAL and a 720x576 video can be
	   displayed without cropping on NTSC.

	   Note that the scaling only occurs on the video stream, the osd
	   resolution is locked to the broadcast standard and not scaled.

	   Thanks to Ian Armstrong for this explanation. */
	h = min(h, 576);
	h = max(h, 2);
	if (id->type == IVTV_DEC_STREAM_TYPE_YUV)
		fmt->fmt.pix.field = field;
	fmt->fmt.pix.width = w;
	fmt->fmt.pix.height = h;
	return ret;
}