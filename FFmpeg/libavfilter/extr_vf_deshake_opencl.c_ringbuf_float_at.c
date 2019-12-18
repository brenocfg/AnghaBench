#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data_end_offset; int data_start_offset; } ;
struct TYPE_5__ {int smooth_window; TYPE_1__ abs_motion; } ;
typedef  TYPE_2__ DeshakeOpenCLContext ;
typedef  int /*<<< orphan*/  AVFifoBuffer ;

/* Variables and functions */
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_fifo_generic_peek_at (int /*<<< orphan*/ *,float*,int,int,int /*<<< orphan*/ *) ; 
 int av_fifo_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ringbuf_float_at(
    DeshakeOpenCLContext *deshake_ctx,
    AVFifoBuffer *values,
    float *val,
    int offset
) {
    int clip_start, clip_end, offset_clipped;
    if (deshake_ctx->abs_motion.data_end_offset != -1) {
        clip_end = deshake_ctx->abs_motion.data_end_offset;
    } else {
        // This expression represents the last valid index in the buffer,
        // which we use repeatedly at the end of the video.
        clip_end = deshake_ctx->smooth_window - (av_fifo_space(values) / sizeof(float)) - 1;
    }

    if (deshake_ctx->abs_motion.data_start_offset != -1) {
        clip_start = deshake_ctx->abs_motion.data_start_offset;
    } else {
        // Negative indices will occur at the start of the video, and we want
        // them to be clipped to 0 in order to repeatedly use the position of
        // the first frame.
        clip_start = 0;
    }

    offset_clipped = av_clip(
        offset,
        clip_start,
        clip_end
    );

    av_fifo_generic_peek_at(
        values,
        val,
        offset_clipped * sizeof(float),
        sizeof(float),
        NULL
    );
}