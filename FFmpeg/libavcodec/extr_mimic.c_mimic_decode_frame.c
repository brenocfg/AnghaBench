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
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_23__ {TYPE_17__* f; } ;
struct TYPE_22__ {int width; int height; int active_thread_type; int /*<<< orphan*/  pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_21__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* bswap_buf ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_20__ {int* num_hblocks; size_t prev_index; size_t cur_index; size_t next_prev_index; int next_cur_index; TYPE_7__* frames; int /*<<< orphan*/  swap_buf; int /*<<< orphan*/  gb; TYPE_1__ bbdsp; int /*<<< orphan*/  swap_buf_size; TYPE_4__* avctx; int /*<<< orphan*/ * num_vblocks; } ;
struct TYPE_18__ {int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ MimicContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/  INT_MAX ; 
 int MIMIC_HEADER_SIZE ; 
 int /*<<< orphan*/  av_fast_padded_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int av_frame_ref (void*,TYPE_17__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int decode (TYPE_2__*,int,int,int) ; 
 int ff_set_dimensions (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  ff_thread_finish_setup (TYPE_4__*) ; 
 int ff_thread_get_buffer (TYPE_4__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ff_thread_report_progress (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flip_swap_frame (void*) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mimic_decode_frame(AVCodecContext *avctx, void *data,
                              int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    int swap_buf_size  = buf_size - MIMIC_HEADER_SIZE;
    MimicContext *ctx  = avctx->priv_data;
    GetByteContext gb;
    int is_pframe;
    int width, height;
    int quality, num_coeffs;
    int res;

    if (buf_size <= MIMIC_HEADER_SIZE) {
        av_log(avctx, AV_LOG_ERROR, "insufficient data\n");
        return AVERROR_INVALIDDATA;
    }

    bytestream2_init(&gb, buf, MIMIC_HEADER_SIZE);
    bytestream2_skip(&gb, 2); /* some constant (always 256) */
    quality    = bytestream2_get_le16u(&gb);
    width      = bytestream2_get_le16u(&gb);
    height     = bytestream2_get_le16u(&gb);
    bytestream2_skip(&gb, 4); /* some constant */
    is_pframe  = bytestream2_get_le32u(&gb);
    num_coeffs = bytestream2_get_byteu(&gb);
    bytestream2_skip(&gb, 3); /* some constant */

    if (!ctx->avctx) {
        int i;

        if (!(width == 160 && height == 120) &&
            !(width == 320 && height == 240)) {
            av_log(avctx, AV_LOG_ERROR, "invalid width/height!\n");
            return AVERROR_INVALIDDATA;
        }

        res = ff_set_dimensions(avctx, width, height);
        if (res < 0)
            return res;

        ctx->avctx     = avctx;
        avctx->pix_fmt = AV_PIX_FMT_YUV420P;
        for (i = 0; i < 3; i++) {
            ctx->num_vblocks[i] = AV_CEIL_RSHIFT(height,   3 + !!i);
            ctx->num_hblocks[i] =                width >> (3 + !!i);
        }
    } else if (width != ctx->avctx->width || height != ctx->avctx->height) {
        avpriv_request_sample(avctx, "Resolution changing");
        return AVERROR_PATCHWELCOME;
    }

    if (is_pframe && !ctx->frames[ctx->prev_index].f->data[0]) {
        av_log(avctx, AV_LOG_ERROR, "decoding must start with keyframe\n");
        return AVERROR_INVALIDDATA;
    }

    ff_thread_release_buffer(avctx, &ctx->frames[ctx->cur_index]);
    ctx->frames[ctx->cur_index].f->pict_type = is_pframe ? AV_PICTURE_TYPE_P :
                                                           AV_PICTURE_TYPE_I;
    if ((res = ff_thread_get_buffer(avctx, &ctx->frames[ctx->cur_index],
                                    AV_GET_BUFFER_FLAG_REF)) < 0)
        return res;

    ctx->next_prev_index = ctx->cur_index;
    ctx->next_cur_index  = (ctx->cur_index - 1) & 15;

    ff_thread_finish_setup(avctx);

    av_fast_padded_malloc(&ctx->swap_buf, &ctx->swap_buf_size, swap_buf_size);
    if (!ctx->swap_buf)
        return AVERROR(ENOMEM);

    ctx->bbdsp.bswap_buf(ctx->swap_buf,
                         (const uint32_t *) (buf + MIMIC_HEADER_SIZE),
                         swap_buf_size >> 2);
    init_get_bits(&ctx->gb, ctx->swap_buf, swap_buf_size << 3);

    res = decode(ctx, quality, num_coeffs, !is_pframe);
    ff_thread_report_progress(&ctx->frames[ctx->cur_index], INT_MAX, 0);
    if (res < 0) {
        if (!(avctx->active_thread_type & FF_THREAD_FRAME))
            ff_thread_release_buffer(avctx, &ctx->frames[ctx->cur_index]);
        return res;
    }

    if ((res = av_frame_ref(data, ctx->frames[ctx->cur_index].f)) < 0)
        return res;
    *got_frame      = 1;

    flip_swap_frame(data);

    ctx->prev_index = ctx->next_prev_index;
    ctx->cur_index  = ctx->next_cur_index;

    return buf_size;
}