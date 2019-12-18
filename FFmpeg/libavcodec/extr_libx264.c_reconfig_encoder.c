#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_vbv_buffer_size; int i_vbv_max_bitrate; scalar_t__ i_rc_method; int i_bitrate; scalar_t__ f_rf_constant; scalar_t__ i_qp_constant; scalar_t__ f_rf_constant_max; } ;
struct TYPE_15__ {int i_sar_height; int i_sar_width; } ;
struct TYPE_23__ {scalar_t__ b_tff; int i_frame_packing; TYPE_3__ rc; TYPE_1__ vui; scalar_t__ b_interlaced; } ;
struct TYPE_18__ {scalar_t__ avcintra_class; scalar_t__ crf; scalar_t__ cqp; scalar_t__ crf_max; TYPE_9__ params; int /*<<< orphan*/  enc; } ;
typedef  TYPE_4__ X264Context ;
struct TYPE_16__ {int num; int den; } ;
struct TYPE_22__ {int rc_buffer_size; int rc_max_rate; int bit_rate; TYPE_2__ sample_aspect_ratio; TYPE_4__* priv_data; } ;
struct TYPE_21__ {scalar_t__ top_field_first; } ;
struct TYPE_20__ {scalar_t__ data; } ;
struct TYPE_19__ {int type; int flags; } ;
typedef  TYPE_5__ AVStereo3D ;
typedef  TYPE_6__ AVFrameSideData ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_FRAME_DATA_STEREO3D ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  AV_STEREO3D_2D 134 
#define  AV_STEREO3D_CHECKERBOARD 133 
#define  AV_STEREO3D_COLUMNS 132 
 int AV_STEREO3D_FLAG_INVERT ; 
#define  AV_STEREO3D_FRAMESEQUENCE 131 
#define  AV_STEREO3D_LINES 130 
#define  AV_STEREO3D_SIDEBYSIDE 129 
#define  AV_STEREO3D_TOPBOTTOM 128 
 scalar_t__ X264_RC_ABR ; 
 scalar_t__ X264_RC_CQP ; 
 scalar_t__ X264_RC_CRF ; 
 TYPE_6__* av_frame_get_side_data (TYPE_7__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  x264_encoder_reconfig (int /*<<< orphan*/ ,TYPE_9__*) ; 

__attribute__((used)) static void reconfig_encoder(AVCodecContext *ctx, const AVFrame *frame)
{
    X264Context *x4 = ctx->priv_data;
    AVFrameSideData *side_data;


  if (x4->avcintra_class < 0) {
    if (x4->params.b_interlaced && x4->params.b_tff != frame->top_field_first) {

        x4->params.b_tff = frame->top_field_first;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }
    if (x4->params.vui.i_sar_height*ctx->sample_aspect_ratio.num != ctx->sample_aspect_ratio.den * x4->params.vui.i_sar_width) {
        x4->params.vui.i_sar_height = ctx->sample_aspect_ratio.den;
        x4->params.vui.i_sar_width  = ctx->sample_aspect_ratio.num;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }

    if (x4->params.rc.i_vbv_buffer_size != ctx->rc_buffer_size / 1000 ||
        x4->params.rc.i_vbv_max_bitrate != ctx->rc_max_rate    / 1000) {
        x4->params.rc.i_vbv_buffer_size = ctx->rc_buffer_size / 1000;
        x4->params.rc.i_vbv_max_bitrate = ctx->rc_max_rate    / 1000;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }

    if (x4->params.rc.i_rc_method == X264_RC_ABR &&
        x4->params.rc.i_bitrate != ctx->bit_rate / 1000) {
        x4->params.rc.i_bitrate = ctx->bit_rate / 1000;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }

    if (x4->crf >= 0 &&
        x4->params.rc.i_rc_method == X264_RC_CRF &&
        x4->params.rc.f_rf_constant != x4->crf) {
        x4->params.rc.f_rf_constant = x4->crf;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }

    if (x4->params.rc.i_rc_method == X264_RC_CQP &&
        x4->cqp >= 0 &&
        x4->params.rc.i_qp_constant != x4->cqp) {
        x4->params.rc.i_qp_constant = x4->cqp;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }

    if (x4->crf_max >= 0 &&
        x4->params.rc.f_rf_constant_max != x4->crf_max) {
        x4->params.rc.f_rf_constant_max = x4->crf_max;
        x264_encoder_reconfig(x4->enc, &x4->params);
    }
  }

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_STEREO3D);
    if (side_data) {
        AVStereo3D *stereo = (AVStereo3D *)side_data->data;
        int fpa_type;

        switch (stereo->type) {
        case AV_STEREO3D_CHECKERBOARD:
            fpa_type = 0;
            break;
        case AV_STEREO3D_COLUMNS:
            fpa_type = 1;
            break;
        case AV_STEREO3D_LINES:
            fpa_type = 2;
            break;
        case AV_STEREO3D_SIDEBYSIDE:
            fpa_type = 3;
            break;
        case AV_STEREO3D_TOPBOTTOM:
            fpa_type = 4;
            break;
        case AV_STEREO3D_FRAMESEQUENCE:
            fpa_type = 5;
            break;
#if X264_BUILD >= 145
        case AV_STEREO3D_2D:
            fpa_type = 6;
            break;
#endif
        default:
            fpa_type = -1;
            break;
        }

        /* Inverted mode is not supported by x264 */
        if (stereo->flags & AV_STEREO3D_FLAG_INVERT) {
            av_log(ctx, AV_LOG_WARNING,
                   "Ignoring unsupported inverted stereo value %d\n", fpa_type);
            fpa_type = -1;
        }

        if (fpa_type != x4->params.i_frame_packing) {
            x4->params.i_frame_packing = fpa_type;
            x264_encoder_reconfig(x4->enc, &x4->params);
        }
    }
}