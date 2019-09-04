#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int i_pts; int i_type; int i_qpplus1; } ;
typedef  TYPE_2__ xavs_picture_t ;
typedef  int /*<<< orphan*/  xavs_nal_t ;
struct TYPE_17__ {int i_plane; int /*<<< orphan*/ * i_stride; int /*<<< orphan*/ * plane; int /*<<< orphan*/  i_csp; } ;
struct TYPE_23__ {int i_pts; int /*<<< orphan*/  i_type; TYPE_1__ img; } ;
struct TYPE_19__ {int* pts_buffer; int out_frame_count; scalar_t__ end_of_stream; TYPE_7__ pic; int /*<<< orphan*/  enc; } ;
typedef  TYPE_3__ XavsContext ;
struct TYPE_22__ {int frame_number; int max_b_frames; scalar_t__ has_b_frames; TYPE_3__* priv_data; } ;
struct TYPE_21__ {int pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {int* data; int dts; int pts; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AV_PICTURE_TYPE_B ; 
 int AV_PICTURE_TYPE_I ; 
 int AV_PICTURE_TYPE_NONE ; 
 int AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 scalar_t__ END_OF_STREAM ; 
 int FF_QP2LAMBDA ; 
 int /*<<< orphan*/  XAVS_CSP_I420 ; 
 int /*<<< orphan*/  XAVS_TYPE_AUTO ; 
#define  XAVS_TYPE_B 132 
#define  XAVS_TYPE_BREF 131 
#define  XAVS_TYPE_I 130 
#define  XAVS_TYPE_IDR 129 
#define  XAVS_TYPE_P 128 
 int encode_nals (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int ff_alloc_packet2 (TYPE_6__*,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_side_data_set_encoder_stats (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xavs_encoder_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,TYPE_7__*,TYPE_2__*) ; 

__attribute__((used)) static int XAVS_frame(AVCodecContext *avctx, AVPacket *pkt,
                      const AVFrame *frame, int *got_packet)
{
    XavsContext *x4 = avctx->priv_data;
    xavs_nal_t *nal;
    int nnal, i, ret;
    xavs_picture_t pic_out;
    int pict_type;

    x4->pic.img.i_csp   = XAVS_CSP_I420;
    x4->pic.img.i_plane = 3;

    if (frame) {
       for (i = 0; i < 3; i++) {
            x4->pic.img.plane[i] = frame->data[i];
            x4->pic.img.i_stride[i] = frame->linesize[i];
       }

        x4->pic.i_pts  = frame->pts;
        x4->pic.i_type = XAVS_TYPE_AUTO;
        x4->pts_buffer[avctx->frame_number % (avctx->max_b_frames+1)] = frame->pts;
    }

    if (xavs_encoder_encode(x4->enc, &nal, &nnal,
                            frame? &x4->pic: NULL, &pic_out) < 0)
    return -1;

    ret = encode_nals(avctx, pkt, nal, nnal);

    if (ret < 0)
        return -1;

    if (!ret) {
        if (!frame && !(x4->end_of_stream)) {
            if ((ret = ff_alloc_packet2(avctx, pkt, 4, 0)) < 0)
                return ret;

            pkt->data[0] = 0x0;
            pkt->data[1] = 0x0;
            pkt->data[2] = 0x01;
            pkt->data[3] = 0xb1;
            pkt->dts = 2*x4->pts_buffer[(x4->out_frame_count-1)%(avctx->max_b_frames+1)] -
                         x4->pts_buffer[(x4->out_frame_count-2)%(avctx->max_b_frames+1)];
            x4->end_of_stream = END_OF_STREAM;
            *got_packet = 1;
        }
        return 0;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->pts = pic_out.i_pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    pkt->pts = pic_out.i_pts;
    if (avctx->has_b_frames) {
        if (!x4->out_frame_count)
            pkt->dts = pkt->pts - (x4->pts_buffer[1] - x4->pts_buffer[0]);
        else
            pkt->dts = x4->pts_buffer[(x4->out_frame_count-1)%(avctx->max_b_frames+1)];
    } else
        pkt->dts = pkt->pts;

    switch (pic_out.i_type) {
    case XAVS_TYPE_IDR:
    case XAVS_TYPE_I:
        pict_type = AV_PICTURE_TYPE_I;
        break;
    case XAVS_TYPE_P:
        pict_type = AV_PICTURE_TYPE_P;
        break;
    case XAVS_TYPE_B:
    case XAVS_TYPE_BREF:
        pict_type = AV_PICTURE_TYPE_B;
        break;
    default:
        pict_type = AV_PICTURE_TYPE_NONE;
    }
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->pict_type = pict_type;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    /* There is no IDR frame in AVS JiZhun */
    /* Sequence header is used as a flag */
    if (pic_out.i_type == XAVS_TYPE_I) {
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        avctx->coded_frame->key_frame = 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
        pkt->flags |= AV_PKT_FLAG_KEY;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->quality = (pic_out.i_qpplus1 - 1) * FF_QP2LAMBDA;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    ff_side_data_set_encoder_stats(pkt, (pic_out.i_qpplus1 - 1) * FF_QP2LAMBDA, NULL, 0, pict_type);

    x4->out_frame_count++;
    *got_packet = ret;
    return 0;
}