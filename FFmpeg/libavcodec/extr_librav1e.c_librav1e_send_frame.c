#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ librav1eContext ;
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {int height; int* linesize; int /*<<< orphan*/ * data; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {int nb_components; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_10__ {int depth; } ;
typedef  int /*<<< orphan*/  RaFrame ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  RA_ENCODER_STATUS_ENOUGH_DATA 130 
#define  RA_ENCODER_STATUS_FAILURE 129 
#define  RA_ENCODER_STATUS_SUCCESS 128 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rav1e_frame_fill_plane (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * rav1e_frame_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rav1e_frame_unref (int /*<<< orphan*/ *) ; 
 int rav1e_send_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rav1e_status_to_str (int) ; 

__attribute__((used)) static int librav1e_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    librav1eContext *ctx = avctx->priv_data;
    RaFrame *rframe = NULL;
    int ret;

    if (frame) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);

        rframe = rav1e_frame_new(ctx->ctx);
        if (!rframe) {
            av_log(avctx, AV_LOG_ERROR, "Could not allocate new rav1e frame.\n");
            return AVERROR(ENOMEM);
        }

        for (int i = 0; i < desc->nb_components; i++) {
            int shift = i ? desc->log2_chroma_h : 0;
            int bytes = desc->comp[0].depth == 8 ? 1 : 2;
            rav1e_frame_fill_plane(rframe, i, frame->data[i],
                                   (frame->height >> shift) * frame->linesize[i],
                                   frame->linesize[i], bytes);
        }
    }

    ret = rav1e_send_frame(ctx->ctx, rframe);
    if (rframe)
         rav1e_frame_unref(rframe); /* No need to unref if flushing. */

    switch (ret) {
    case RA_ENCODER_STATUS_SUCCESS:
        break;
    case RA_ENCODER_STATUS_ENOUGH_DATA:
        return AVERROR(EAGAIN);
    case RA_ENCODER_STATUS_FAILURE:
        av_log(avctx, AV_LOG_ERROR, "Could not send frame: %s\n", rav1e_status_to_str(ret));
        return AVERROR_EXTERNAL;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown return code %d from rav1e_send_frame: %s\n", ret, rav1e_status_to_str(ret));
        return AVERROR_UNKNOWN;
    }

    return 0;
}