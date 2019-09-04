#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ type; int quant; int /*<<< orphan*/  hlength; void* version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ xvid_enc_stats_t ;
struct TYPE_20__ {int /*<<< orphan*/ * stride; int /*<<< orphan*/ * plane; int /*<<< orphan*/  csp; } ;
struct TYPE_23__ {int length; int par_width; int par_height; int quant; int out_flags; int /*<<< orphan*/  quant_inter_matrix; int /*<<< orphan*/  quant_intra_matrix; int /*<<< orphan*/  par; scalar_t__ type; int /*<<< orphan*/  motion; int /*<<< orphan*/  vol_flags; int /*<<< orphan*/  vop_flags; TYPE_1__ input; scalar_t__ bitstream; void* version; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ xvid_enc_frame_t ;
struct xvid_context {char* twopassbuffer; char* old_twopassbuffer; scalar_t__ quicktime_format; int /*<<< orphan*/  encoder_handle; int /*<<< orphan*/  inter_matrix; int /*<<< orphan*/  intra_matrix; scalar_t__ qscale; int /*<<< orphan*/  me_flags; int /*<<< orphan*/  vol_flags; int /*<<< orphan*/  vop_flags; } ;
typedef  int int64_t ;
struct TYPE_21__ {int num; int den; } ;
struct TYPE_26__ {int width; int height; scalar_t__ pix_fmt; scalar_t__* stats_out; TYPE_2__ sample_aspect_ratio; struct xvid_context* priv_data; } ;
struct TYPE_25__ {int pict_type; int quality; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {int size; int /*<<< orphan*/  flags; scalar_t__ data; } ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 scalar_t__ AV_INPUT_BUFFER_MIN_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_P ; 
 int AV_PICTURE_TYPE_S ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_QP2LAMBDA ; 
 int MAX_MB_BYTES ; 
 int /*<<< orphan*/  XVID_CSP_PLANAR ; 
 int /*<<< orphan*/  XVID_ENC_ENCODE ; 
 int XVID_KEYFRAME ; 
 int /*<<< orphan*/  XVID_PAR_EXT ; 
 scalar_t__ XVID_TYPE_AUTO ; 
 scalar_t__ XVID_TYPE_BVOP ; 
 scalar_t__ XVID_TYPE_IVOP ; 
 scalar_t__ XVID_TYPE_PVOP ; 
 scalar_t__ XVID_TYPE_SVOP ; 
 void* XVID_VERSION ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,int,int,int) ; 
 int ff_alloc_packet2 (TYPE_7__*,TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_5__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int xvid_encore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*) ; 
 int xvid_strip_vol_header (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xvid_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                             const AVFrame *picture, int *got_packet)
{
    int xerr, i, ret, user_packet = !!pkt->data;
    struct xvid_context *x = avctx->priv_data;
    int mb_width  = (avctx->width  + 15) / 16;
    int mb_height = (avctx->height + 15) / 16;
    char *tmp;

    xvid_enc_frame_t xvid_enc_frame = { 0 };
    xvid_enc_stats_t xvid_enc_stats = { 0 };

    if ((ret = ff_alloc_packet2(avctx, pkt, mb_width*(int64_t)mb_height*MAX_MB_BYTES + AV_INPUT_BUFFER_MIN_SIZE, 0)) < 0)
        return ret;

    /* Start setting up the frame */
    xvid_enc_frame.version = XVID_VERSION;
    xvid_enc_stats.version = XVID_VERSION;

    /* Let Xvid know where to put the frame. */
    xvid_enc_frame.bitstream = pkt->data;
    xvid_enc_frame.length    = pkt->size;

    /* Initialize input image fields */
    if (avctx->pix_fmt != AV_PIX_FMT_YUV420P) {
        av_log(avctx, AV_LOG_ERROR,
               "Xvid: Color spaces other than 420P not supported\n");
        return AVERROR(EINVAL);
    }

    xvid_enc_frame.input.csp = XVID_CSP_PLANAR; /* YUV420P */

    for (i = 0; i < 4; i++) {
        xvid_enc_frame.input.plane[i]  = picture->data[i];
        xvid_enc_frame.input.stride[i] = picture->linesize[i];
    }

    /* Encoder Flags */
    xvid_enc_frame.vop_flags = x->vop_flags;
    xvid_enc_frame.vol_flags = x->vol_flags;
    xvid_enc_frame.motion    = x->me_flags;
    xvid_enc_frame.type      =
        picture->pict_type == AV_PICTURE_TYPE_I ? XVID_TYPE_IVOP :
        picture->pict_type == AV_PICTURE_TYPE_P ? XVID_TYPE_PVOP :
        picture->pict_type == AV_PICTURE_TYPE_B ? XVID_TYPE_BVOP :
                                                  XVID_TYPE_AUTO;

    /* Pixel aspect ratio setting */
    if (avctx->sample_aspect_ratio.num < 0 || avctx->sample_aspect_ratio.num > 255 ||
        avctx->sample_aspect_ratio.den < 0 || avctx->sample_aspect_ratio.den > 255) {
        av_log(avctx, AV_LOG_WARNING,
               "Invalid pixel aspect ratio %i/%i, limit is 255/255 reducing\n",
               avctx->sample_aspect_ratio.num, avctx->sample_aspect_ratio.den);
        av_reduce(&avctx->sample_aspect_ratio.num, &avctx->sample_aspect_ratio.den,
                   avctx->sample_aspect_ratio.num,  avctx->sample_aspect_ratio.den, 255);
    }
    xvid_enc_frame.par        = XVID_PAR_EXT;
    xvid_enc_frame.par_width  = avctx->sample_aspect_ratio.num;
    xvid_enc_frame.par_height = avctx->sample_aspect_ratio.den;

    /* Quant Setting */
    if (x->qscale)
        xvid_enc_frame.quant = picture->quality / FF_QP2LAMBDA;
    else
        xvid_enc_frame.quant = 0;

    /* Matrices */
    xvid_enc_frame.quant_intra_matrix = x->intra_matrix;
    xvid_enc_frame.quant_inter_matrix = x->inter_matrix;

    /* Encode */
    xerr = xvid_encore(x->encoder_handle, XVID_ENC_ENCODE,
                       &xvid_enc_frame, &xvid_enc_stats);

    /* Two-pass log buffer swapping */
    avctx->stats_out = NULL;
    if (x->twopassbuffer) {
        tmp                  = x->old_twopassbuffer;
        x->old_twopassbuffer = x->twopassbuffer;
        x->twopassbuffer     = tmp;
        x->twopassbuffer[0]  = 0;
        if (x->old_twopassbuffer[0] != 0) {
            avctx->stats_out = x->old_twopassbuffer;
        }
    }

    if (xerr > 0) {
        int pict_type;

        *got_packet = 1;

        if (xvid_enc_stats.type == XVID_TYPE_PVOP)
            pict_type = AV_PICTURE_TYPE_P;
        else if (xvid_enc_stats.type == XVID_TYPE_BVOP)
            pict_type = AV_PICTURE_TYPE_B;
        else if (xvid_enc_stats.type == XVID_TYPE_SVOP)
            pict_type = AV_PICTURE_TYPE_S;
        else
            pict_type = AV_PICTURE_TYPE_I;

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        avctx->coded_frame->pict_type = pict_type;
        avctx->coded_frame->quality = xvid_enc_stats.quant * FF_QP2LAMBDA;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

        ff_side_data_set_encoder_stats(pkt, xvid_enc_stats.quant * FF_QP2LAMBDA, NULL, 0, pict_type);

        if (xvid_enc_frame.out_flags & XVID_KEYFRAME) {
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
            avctx->coded_frame->key_frame = 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            pkt->flags  |= AV_PKT_FLAG_KEY;
            if (x->quicktime_format)
                return xvid_strip_vol_header(avctx, pkt,
                                             xvid_enc_stats.hlength, xerr);
        } else {
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
            avctx->coded_frame->key_frame = 0;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
        }

        pkt->size = xerr;

        return 0;
    } else {
        if (!user_packet)
            av_packet_unref(pkt);
        if (!xerr)
            return 0;
        av_log(avctx, AV_LOG_ERROR,
               "Xvid: Encoding Error Occurred: %i\n", xerr);
        return AVERROR_EXTERNAL;
    }
}