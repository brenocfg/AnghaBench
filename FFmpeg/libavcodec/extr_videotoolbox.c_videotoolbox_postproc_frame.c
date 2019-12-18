#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {scalar_t__ hw_frames_ctx; scalar_t__ pixbuf; } ;
typedef  TYPE_2__ VTHWFrame ;
struct TYPE_8__ {int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/ ** data; scalar_t__ crop_bottom; scalar_t__ crop_top; scalar_t__ crop_left; scalar_t__ crop_right; TYPE_1__** buf; } ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int videotoolbox_postproc_frame(void *avctx, AVFrame *frame)
{
    VTHWFrame *ref = (VTHWFrame *)frame->buf[0]->data;

    if (!ref->pixbuf) {
        av_log(avctx, AV_LOG_ERROR, "No frame decoded?\n");
        av_frame_unref(frame);
        return AVERROR_EXTERNAL;
    }

    frame->crop_right = 0;
    frame->crop_left = 0;
    frame->crop_top = 0;
    frame->crop_bottom = 0;

    frame->data[3] = (uint8_t*)ref->pixbuf;

    if (ref->hw_frames_ctx) {
        av_buffer_unref(&frame->hw_frames_ctx);
        frame->hw_frames_ctx = av_buffer_ref(ref->hw_frames_ctx);
        if (!frame->hw_frames_ctx)
            return AVERROR(ENOMEM);
    }

    return 0;
}