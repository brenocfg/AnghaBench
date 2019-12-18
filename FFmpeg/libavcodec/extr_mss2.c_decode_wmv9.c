#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* mss2_blit_wmv9 ) (scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ;int /*<<< orphan*/  (* mss2_blit_wmv9_masked ) (scalar_t__,int,int,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ;int /*<<< orphan*/  (* upsample_plane ) (int /*<<< orphan*/ ,scalar_t__,int,int) ;} ;
struct TYPE_17__ {TYPE_7__* f; } ;
struct TYPE_20__ {int loop_filter; scalar_t__ pict_type; int end_mb_y; int mb_width; int mb_height; int /*<<< orphan*/  avctx; TYPE_1__ current_picture; int /*<<< orphan*/  er; int /*<<< orphan*/  gb; } ;
struct TYPE_21__ {int rgb_stride; int pal_stride; scalar_t__ rgb_pic; scalar_t__ pal_pic; } ;
struct TYPE_19__ {int bits; int end_mb_x; int respic; TYPE_2__ dsp; TYPE_4__ s; TYPE_6__ c; } ;
typedef  TYPE_3__ VC1Context ;
struct TYPE_23__ {scalar_t__ skip_loop_filter; void* pix_fmt; TYPE_3__* priv_data; } ;
struct TYPE_22__ {scalar_t__* linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ MpegEncContext ;
typedef  TYPE_3__ MSS2Context ;
typedef  TYPE_6__ MSS12Context ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 void* AV_PIX_FMT_RGB24 ; 
 void* AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_er_frame_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mpeg_er_frame_start (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_mpeg_flush (TYPE_8__*) ; 
 int /*<<< orphan*/  ff_mpv_frame_end (TYPE_4__*) ; 
 int ff_mpv_frame_start (TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ff_vc1_decode_blocks (TYPE_3__*) ; 
 scalar_t__ ff_vc1_parse_frame_header (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int,int,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int decode_wmv9(AVCodecContext *avctx, const uint8_t *buf, int buf_size,
                       int x, int y, int w, int h, int wmv9_mask)
{
    MSS2Context *ctx  = avctx->priv_data;
    MSS12Context *c   = &ctx->c;
    VC1Context *v     = avctx->priv_data;
    MpegEncContext *s = &v->s;
    AVFrame *f;
    int ret;

    ff_mpeg_flush(avctx);

    if ((ret = init_get_bits8(&s->gb, buf, buf_size)) < 0)
        return ret;

    s->loop_filter = avctx->skip_loop_filter < AVDISCARD_ALL;

    if (ff_vc1_parse_frame_header(v, &s->gb) < 0) {
        av_log(v->s.avctx, AV_LOG_ERROR, "header error\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->pict_type != AV_PICTURE_TYPE_I) {
        av_log(v->s.avctx, AV_LOG_ERROR, "expected I-frame\n");
        return AVERROR_INVALIDDATA;
    }

    avctx->pix_fmt = AV_PIX_FMT_YUV420P;

    if ((ret = ff_mpv_frame_start(s, avctx)) < 0) {
        av_log(v->s.avctx, AV_LOG_ERROR, "ff_mpv_frame_start error\n");
        avctx->pix_fmt = AV_PIX_FMT_RGB24;
        return ret;
    }

    ff_mpeg_er_frame_start(s);

    v->bits = buf_size * 8;

    v->end_mb_x = (w + 15) >> 4;
    s->end_mb_y = (h + 15) >> 4;
    if (v->respic & 1)
        v->end_mb_x = v->end_mb_x + 1 >> 1;
    if (v->respic & 2)
        s->end_mb_y = s->end_mb_y + 1 >> 1;

    ff_vc1_decode_blocks(v);

    if (v->end_mb_x == s->mb_width && s->end_mb_y == s->mb_height) {
        ff_er_frame_end(&s->er);
    } else {
        av_log(v->s.avctx, AV_LOG_WARNING,
               "disabling error correction due to block count mismatch %dx%d != %dx%d\n",
               v->end_mb_x, s->end_mb_y, s->mb_width, s->mb_height);
    }

    ff_mpv_frame_end(s);

    f = s->current_picture.f;

    if (v->respic == 3) {
        ctx->dsp.upsample_plane(f->data[0], f->linesize[0], w,      h);
        ctx->dsp.upsample_plane(f->data[1], f->linesize[1], w+1 >> 1, h+1 >> 1);
        ctx->dsp.upsample_plane(f->data[2], f->linesize[2], w+1 >> 1, h+1 >> 1);
    } else if (v->respic)
        avpriv_request_sample(v->s.avctx,
                              "Asymmetric WMV9 rectangle subsampling");

    av_assert0(f->linesize[1] == f->linesize[2]);

    if (wmv9_mask != -1)
        ctx->dsp.mss2_blit_wmv9_masked(c->rgb_pic + y * c->rgb_stride + x * 3,
                                       c->rgb_stride, wmv9_mask,
                                       c->pal_pic + y * c->pal_stride + x,
                                       c->pal_stride,
                                       f->data[0], f->linesize[0],
                                       f->data[1], f->data[2], f->linesize[1],
                                       w, h);
    else
        ctx->dsp.mss2_blit_wmv9(c->rgb_pic + y * c->rgb_stride + x * 3,
                                c->rgb_stride,
                                f->data[0], f->linesize[0],
                                f->data[1], f->data[2], f->linesize[1],
                                w, h);

    avctx->pix_fmt = AV_PIX_FMT_RGB24;

    return 0;
}