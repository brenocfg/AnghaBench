#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int crop_warned; int roi_warned; int /*<<< orphan*/  roi_allowed; } ;
typedef  TYPE_1__ VAAPIEncodeContext ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {scalar_t__ crop_right; scalar_t__ crop_left; scalar_t__ crop_bottom; scalar_t__ crop_top; } ;
typedef  int /*<<< orphan*/  AVFrameSideData ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_FRAME_DATA_REGIONS_OF_INTEREST ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/ * av_frame_get_side_data (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vaapi_encode_check_frame(AVCodecContext *avctx,
                                    const AVFrame *frame)
{
    VAAPIEncodeContext *ctx = avctx->priv_data;

    if ((frame->crop_top  || frame->crop_bottom ||
         frame->crop_left || frame->crop_right) && !ctx->crop_warned) {
        av_log(avctx, AV_LOG_WARNING, "Cropping information on input "
               "frames ignored due to lack of API support.\n");
        ctx->crop_warned = 1;
    }

    if (!ctx->roi_allowed) {
        AVFrameSideData *sd =
            av_frame_get_side_data(frame, AV_FRAME_DATA_REGIONS_OF_INTEREST);

        if (sd && !ctx->roi_warned) {
            av_log(avctx, AV_LOG_WARNING, "ROI side data on input "
                   "frames ignored due to lack of driver support.\n");
            ctx->roi_warned = 1;
        }
    }

    return 0;
}