#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct yuv_playback_info {size_t draw_frame; int /*<<< orphan*/  v4l2_src_h; int /*<<< orphan*/  v4l2_src_w; int /*<<< orphan*/  main_rect; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct ivtv_dma_frame {int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; int /*<<< orphan*/  dst; TYPE_1__ src; int /*<<< orphan*/ * uv_source; int /*<<< orphan*/ * y_source; } ;
struct ivtv {scalar_t__ dma_data_req_offset; struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ivtv_yuv_next_free (struct ivtv*) ; 
 int /*<<< orphan*/  ivtv_yuv_setup_frame (struct ivtv*,struct ivtv_dma_frame*) ; 
 scalar_t__* yuv_offset ; 

void ivtv_yuv_setup_stream_frame(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	struct ivtv_dma_frame dma_args;

	ivtv_yuv_next_free(itv);

	/* Copy V4L2 parameters to an ivtv_dma_frame struct... */
	dma_args.y_source = NULL;
	dma_args.uv_source = NULL;
	dma_args.src.left = 0;
	dma_args.src.top = 0;
	dma_args.src.width = yi->v4l2_src_w;
	dma_args.src.height = yi->v4l2_src_h;
	dma_args.dst = yi->main_rect;
	dma_args.src_width = yi->v4l2_src_w;
	dma_args.src_height = yi->v4l2_src_h;

	/* ... and use the same setup routine as ivtv_yuv_prep_frame */
	ivtv_yuv_setup_frame(itv, &dma_args);

	if (!itv->dma_data_req_offset)
		itv->dma_data_req_offset = yuv_offset[yi->draw_frame];
}