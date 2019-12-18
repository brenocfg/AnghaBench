#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  enum ColorMode { ____Placeholder_ColorMode } ColorMode ;
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;
struct TYPE_27__ {int /*<<< orphan*/  c7; int /*<<< orphan*/  c6; int /*<<< orphan*/  c5; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; TYPE_4__* dst; TYPE_4__* src; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_31__ {TYPE_1__* internal; TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_30__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_29__ {int colorspace; scalar_t__ format; int height; } ;
struct TYPE_28__ {int source; int mode; int dest; int /*<<< orphan*/ *** yuv_convert; } ;
struct TYPE_26__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ ColorMatrixContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
#define  AVCOL_SPC_BT2020_CL 139 
#define  AVCOL_SPC_BT2020_NCL 138 
#define  AVCOL_SPC_BT470BG 137 
#define  AVCOL_SPC_BT709 136 
#define  AVCOL_SPC_FCC 135 
#define  AVCOL_SPC_SMPTE170M 134 
#define  AVCOL_SPC_SMPTE240M 133 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 scalar_t__ AV_PIX_FMT_YUV444P ; 
#define  COLOR_MODE_BT2020 132 
#define  COLOR_MODE_BT601 131 
#define  COLOR_MODE_BT709 130 
#define  COLOR_MODE_FCC 129 
 int COLOR_MODE_NONE ; 
#define  COLOR_MODE_SMPTE240M 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_slice_uyvy422 ; 
 int /*<<< orphan*/  process_slice_yuv420p ; 
 int /*<<< orphan*/  process_slice_yuv422p ; 
 int /*<<< orphan*/  process_slice_yuv444p ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *link, AVFrame *in)
{
    AVFilterContext *ctx = link->dst;
    ColorMatrixContext *color = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    ThreadData td = {0};

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    if (color->source == COLOR_MODE_NONE) {
        enum AVColorSpace cs = in->colorspace;
        enum ColorMode source;

        switch(cs) {
        case AVCOL_SPC_BT709     : source = COLOR_MODE_BT709     ; break;
        case AVCOL_SPC_FCC       : source = COLOR_MODE_FCC       ; break;
        case AVCOL_SPC_SMPTE240M : source = COLOR_MODE_SMPTE240M ; break;
        case AVCOL_SPC_BT470BG   : source = COLOR_MODE_BT601     ; break;
        case AVCOL_SPC_SMPTE170M : source = COLOR_MODE_BT601     ; break;
        case AVCOL_SPC_BT2020_NCL: source = COLOR_MODE_BT2020    ; break;
        case AVCOL_SPC_BT2020_CL : source = COLOR_MODE_BT2020    ; break;
        default :
            av_log(ctx, AV_LOG_ERROR, "Input frame does not specify a supported colorspace, and none has been specified as source either\n");
            av_frame_free(&out);
            return AVERROR(EINVAL);
        }
        color->mode = source * 5 + color->dest;
    } else
        color->mode = color->source * 5 + color->dest;

    switch(color->dest) {
    case COLOR_MODE_BT709    : out->colorspace = AVCOL_SPC_BT709     ; break;
    case COLOR_MODE_FCC      : out->colorspace = AVCOL_SPC_FCC       ; break;
    case COLOR_MODE_SMPTE240M: out->colorspace = AVCOL_SPC_SMPTE240M ; break;
    case COLOR_MODE_BT601    : out->colorspace = AVCOL_SPC_BT470BG   ; break;
    case COLOR_MODE_BT2020   : out->colorspace = AVCOL_SPC_BT2020_NCL; break;
    }

    td.src = in;
    td.dst = out;
    td.c2 = color->yuv_convert[color->mode][0][1];
    td.c3 = color->yuv_convert[color->mode][0][2];
    td.c4 = color->yuv_convert[color->mode][1][1];
    td.c5 = color->yuv_convert[color->mode][1][2];
    td.c6 = color->yuv_convert[color->mode][2][1];
    td.c7 = color->yuv_convert[color->mode][2][2];

    if (in->format == AV_PIX_FMT_YUV444P)
        ctx->internal->execute(ctx, process_slice_yuv444p, &td, NULL,
                               FFMIN(in->height, ff_filter_get_nb_threads(ctx)));
    else if (in->format == AV_PIX_FMT_YUV422P)
        ctx->internal->execute(ctx, process_slice_yuv422p, &td, NULL,
                               FFMIN(in->height, ff_filter_get_nb_threads(ctx)));
    else if (in->format == AV_PIX_FMT_YUV420P)
        ctx->internal->execute(ctx, process_slice_yuv420p, &td, NULL,
                               FFMIN(in->height / 2, ff_filter_get_nb_threads(ctx)));
    else
        ctx->internal->execute(ctx, process_slice_uyvy422, &td, NULL,
                               FFMIN(in->height, ff_filter_get_nb_threads(ctx)));

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}