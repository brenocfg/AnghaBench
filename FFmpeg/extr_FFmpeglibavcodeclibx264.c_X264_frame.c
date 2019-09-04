#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_23__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_14__ ;
typedef  struct TYPE_33__   TYPE_13__ ;
typedef  struct TYPE_32__   TYPE_12__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
struct TYPE_42__ {int i_type; int b_keyframe; int i_qpplus1; int /*<<< orphan*/ * opaque; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ x264_picture_t ;
typedef  int /*<<< orphan*/  x264_nal_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_39__ {float* quant_offsets; int /*<<< orphan*/  (* quant_offsets_free ) (float*) ;} ;
struct TYPE_35__ {int num_payloads; TYPE_23__* payloads; int /*<<< orphan*/  (* sei_free ) (float*) ;} ;
struct TYPE_41__ {int i_plane; int /*<<< orphan*/ * i_stride; int /*<<< orphan*/ * plane; int /*<<< orphan*/  i_csp; } ;
struct TYPE_34__ {int i_type; TYPE_4__ prop; TYPE_1__ extra_sei; int /*<<< orphan*/ * opaque; int /*<<< orphan*/  i_pts; TYPE_6__ img; } ;
struct TYPE_37__ {scalar_t__ i_aq_mode; } ;
struct TYPE_40__ {TYPE_2__ rc; int /*<<< orphan*/  i_csp; } ;
struct TYPE_43__ {size_t next_reordered_opaque; size_t nb_reordered_opaque; int /*<<< orphan*/ * reordered_opaque; TYPE_14__ pic; int /*<<< orphan*/  enc; TYPE_5__ params; scalar_t__ a53_cc; int /*<<< orphan*/  forced_idr; } ;
typedef  TYPE_8__ X264Context ;
struct TYPE_38__ {float den; float num; } ;
struct TYPE_44__ {int top; int bottom; int left; int right; scalar_t__ self_size; TYPE_3__ qoffset; } ;
struct TYPE_36__ {size_t payload_size; int payload_type; void* payload; } ;
struct TYPE_33__ {int /*<<< orphan*/  reordered_opaque; int /*<<< orphan*/  pix_fmt; TYPE_8__* priv_data; } ;
struct TYPE_32__ {int pict_type; scalar_t__ interlaced_frame; int width; int height; int /*<<< orphan*/  reordered_opaque; int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {int size; scalar_t__ data; } ;
struct TYPE_30__ {int flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_9__ AVRegionOfInterest ;
typedef  TYPE_10__ AVPacket ;
typedef  TYPE_11__ AVFrameSideData ;
typedef  TYPE_12__ AVFrame ;
typedef  TYPE_13__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_FRAME_DATA_REGIONS_OF_INTEREST ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  AV_PICTURE_TYPE_B 135 
#define  AV_PICTURE_TYPE_I 134 
 int AV_PICTURE_TYPE_NONE ; 
#define  AV_PICTURE_TYPE_P 133 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int FF_QP2LAMBDA ; 
 int MB_SIZE ; 
 scalar_t__ X264_AQ_NONE ; 
 int /*<<< orphan*/  X264_CSP_HIGH_DEPTH ; 
 int X264_TYPE_AUTO ; 
#define  X264_TYPE_B 132 
#define  X264_TYPE_BREF 131 
#define  X264_TYPE_I 130 
#define  X264_TYPE_IDR 129 
 int X264_TYPE_KEYFRAME ; 
#define  X264_TYPE_P 128 
 float av_clipf (float,float,float) ; 
 TYPE_11__* av_frame_get_side_data (TYPE_12__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (float*) ; 
 int /*<<< orphan*/  av_log (TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_23__* av_mallocz (int) ; 
 float* av_mallocz_array (int,int) ; 
 int avfmt2_num_planes (int /*<<< orphan*/ ) ; 
 int encode_nals (TYPE_13__*,TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int ff_alloc_a53_sei (TYPE_12__ const*,int /*<<< orphan*/ ,void**,size_t*) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_10__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reconfig_encoder (TYPE_13__*,TYPE_12__ const*) ; 
 int x264_bit_depth ; 
 scalar_t__ x264_encoder_delayed_frames (int /*<<< orphan*/ ) ; 
 scalar_t__ x264_encoder_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,TYPE_14__*,TYPE_7__*) ; 
 int /*<<< orphan*/  x264_picture_init (TYPE_14__*) ; 

__attribute__((used)) static int X264_frame(AVCodecContext *ctx, AVPacket *pkt, const AVFrame *frame,
                      int *got_packet)
{
    X264Context *x4 = ctx->priv_data;
    x264_nal_t *nal;
    int nnal, i, ret;
    x264_picture_t pic_out = {0};
    int pict_type;
    int64_t *out_opaque;
    AVFrameSideData *sd;

    x264_picture_init( &x4->pic );
    x4->pic.img.i_csp   = x4->params.i_csp;
#if X264_BUILD >= 153
    if (x4->params.i_bitdepth > 8)
#else
    if (x264_bit_depth > 8)
#endif
        x4->pic.img.i_csp |= X264_CSP_HIGH_DEPTH;
    x4->pic.img.i_plane = avfmt2_num_planes(ctx->pix_fmt);

    if (frame) {
        for (i = 0; i < x4->pic.img.i_plane; i++) {
            x4->pic.img.plane[i]    = frame->data[i];
            x4->pic.img.i_stride[i] = frame->linesize[i];
        }

        x4->pic.i_pts  = frame->pts;

        x4->reordered_opaque[x4->next_reordered_opaque] = frame->reordered_opaque;
        x4->pic.opaque = &x4->reordered_opaque[x4->next_reordered_opaque];
        x4->next_reordered_opaque++;
        x4->next_reordered_opaque %= x4->nb_reordered_opaque;

        switch (frame->pict_type) {
        case AV_PICTURE_TYPE_I:
            x4->pic.i_type = x4->forced_idr > 0 ? X264_TYPE_IDR
                                                : X264_TYPE_KEYFRAME;
            break;
        case AV_PICTURE_TYPE_P:
            x4->pic.i_type = X264_TYPE_P;
            break;
        case AV_PICTURE_TYPE_B:
            x4->pic.i_type = X264_TYPE_B;
            break;
        default:
            x4->pic.i_type = X264_TYPE_AUTO;
            break;
        }
        reconfig_encoder(ctx, frame);

        if (x4->a53_cc) {
            void *sei_data;
            size_t sei_size;

            ret = ff_alloc_a53_sei(frame, 0, &sei_data, &sei_size);
            if (ret < 0) {
                av_log(ctx, AV_LOG_ERROR, "Not enough memory for closed captions, skipping\n");
            } else if (sei_data) {
                x4->pic.extra_sei.payloads = av_mallocz(sizeof(x4->pic.extra_sei.payloads[0]));
                if (x4->pic.extra_sei.payloads == NULL) {
                    av_log(ctx, AV_LOG_ERROR, "Not enough memory for closed captions, skipping\n");
                    av_free(sei_data);
                } else {
                    x4->pic.extra_sei.sei_free = av_free;

                    x4->pic.extra_sei.payloads[0].payload_size = sei_size;
                    x4->pic.extra_sei.payloads[0].payload = sei_data;
                    x4->pic.extra_sei.num_payloads = 1;
                    x4->pic.extra_sei.payloads[0].payload_type = 4;
                }
            }
        }

        sd = av_frame_get_side_data(frame, AV_FRAME_DATA_REGIONS_OF_INTEREST);
        if (sd) {
            if (x4->params.rc.i_aq_mode == X264_AQ_NONE) {
                av_log(ctx, AV_LOG_WARNING, "Adaptive quantization must be enabled to use ROI encoding, skipping ROI.\n");
            } else {
                if (frame->interlaced_frame == 0) {
                    int mbx = (frame->width + MB_SIZE - 1) / MB_SIZE;
                    int mby = (frame->height + MB_SIZE - 1) / MB_SIZE;
                    int nb_rois;
                    AVRegionOfInterest* roi;
                    float* qoffsets;
                    qoffsets = av_mallocz_array(mbx * mby, sizeof(*qoffsets));
                    if (!qoffsets)
                        return AVERROR(ENOMEM);

                    nb_rois = sd->size / sizeof(AVRegionOfInterest);
                    roi = (AVRegionOfInterest*)sd->data;
                    for (int count = 0; count < nb_rois; count++) {
                        int starty = FFMIN(mby, roi->top / MB_SIZE);
                        int endy   = FFMIN(mby, (roi->bottom + MB_SIZE - 1)/ MB_SIZE);
                        int startx = FFMIN(mbx, roi->left / MB_SIZE);
                        int endx   = FFMIN(mbx, (roi->right + MB_SIZE - 1)/ MB_SIZE);
                        float qoffset;

                        if (roi->qoffset.den == 0) {
                            av_free(qoffsets);
                            av_log(ctx, AV_LOG_ERROR, "AVRegionOfInterest.qoffset.den should not be zero.\n");
                            return AVERROR(EINVAL);
                        }
                        qoffset = roi->qoffset.num * 1.0f / roi->qoffset.den;
                        qoffset = av_clipf(qoffset, -1.0f, 1.0f);

                        // 25 is a number that I think it is a possible proper scale value.
                        qoffset = qoffset * 25;

                        for (int y = starty; y < endy; y++) {
                            for (int x = startx; x < endx; x++) {
                                qoffsets[x + y*mbx] = qoffset;
                            }
                        }

                        if (roi->self_size == 0) {
                            av_free(qoffsets);
                            av_log(ctx, AV_LOG_ERROR, "AVRegionOfInterest.self_size should be set to sizeof(AVRegionOfInterest).\n");
                            return AVERROR(EINVAL);
                        }
                        roi = (AVRegionOfInterest*)((char*)roi + roi->self_size);
                    }

                    x4->pic.prop.quant_offsets = qoffsets;
                    x4->pic.prop.quant_offsets_free = av_free;
                } else {
                    av_log(ctx, AV_LOG_WARNING, "interlaced_frame not supported for ROI encoding yet, skipping ROI.\n");
                }
            }
        }
    }

    do {
        if (x264_encoder_encode(x4->enc, &nal, &nnal, frame? &x4->pic: NULL, &pic_out) < 0)
            return AVERROR_EXTERNAL;

        ret = encode_nals(ctx, pkt, nal, nnal);
        if (ret < 0)
            return ret;
    } while (!ret && !frame && x264_encoder_delayed_frames(x4->enc));

    pkt->pts = pic_out.i_pts;
    pkt->dts = pic_out.i_dts;

    out_opaque = pic_out.opaque;
    if (out_opaque >= x4->reordered_opaque &&
        out_opaque < &x4->reordered_opaque[x4->nb_reordered_opaque]) {
        ctx->reordered_opaque = *out_opaque;
    } else {
        // Unexpected opaque pointer on picture output
        ctx->reordered_opaque = 0;
    }

    switch (pic_out.i_type) {
    case X264_TYPE_IDR:
    case X264_TYPE_I:
        pict_type = AV_PICTURE_TYPE_I;
        break;
    case X264_TYPE_P:
        pict_type = AV_PICTURE_TYPE_P;
        break;
    case X264_TYPE_B:
    case X264_TYPE_BREF:
        pict_type = AV_PICTURE_TYPE_B;
        break;
    default:
        pict_type = AV_PICTURE_TYPE_NONE;
    }
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    ctx->coded_frame->pict_type = pict_type;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    pkt->flags |= AV_PKT_FLAG_KEY*pic_out.b_keyframe;
    if (ret) {
        ff_side_data_set_encoder_stats(pkt, (pic_out.i_qpplus1 - 1) * FF_QP2LAMBDA, NULL, 0, pict_type);

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        ctx->coded_frame->quality = (pic_out.i_qpplus1 - 1) * FF_QP2LAMBDA;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    }

    *got_packet = ret;
    return 0;
}