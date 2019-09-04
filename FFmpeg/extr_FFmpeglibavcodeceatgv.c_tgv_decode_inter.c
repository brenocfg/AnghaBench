#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_8__ {int num_mvs; int** mv_codebook; int num_blocks_packed; int** block_codebook; TYPE_1__* last_frame; TYPE_6__* avctx; } ;
typedef  TYPE_2__ TgvContext ;
struct TYPE_10__ {int height; int width; } ;
struct TYPE_9__ {int** data; int* linesize; } ;
struct TYPE_7__ {int** data; int* linesize; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL16 (int const*) ; 
 int MIN_CACHE_BITS ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int,...) ; 
 int av_reallocp (int***,int) ; 
 int av_reallocp_array (int***,int,int) ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 void* get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int tgv_decode_inter(TgvContext *s, AVFrame *frame,
                            const uint8_t *buf, const uint8_t *buf_end)
{
    int num_mvs;
    int num_blocks_raw;
    int num_blocks_packed;
    int vector_bits;
    int i,j,x,y;
    GetBitContext gb;
    int mvbits;
    const uint8_t *blocks_raw;

    if(buf_end - buf < 12)
        return AVERROR_INVALIDDATA;

    num_mvs           = AV_RL16(&buf[0]);
    num_blocks_raw    = AV_RL16(&buf[2]);
    num_blocks_packed = AV_RL16(&buf[4]);
    vector_bits       = AV_RL16(&buf[6]);
    buf += 12;

    if (vector_bits > MIN_CACHE_BITS || !vector_bits) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Invalid value for motion vector bits: %d\n", vector_bits);
        return AVERROR_INVALIDDATA;
    }

    /* allocate codebook buffers as necessary */
    if (num_mvs > s->num_mvs) {
        int err = av_reallocp_array(&s->mv_codebook, num_mvs, sizeof(*s->mv_codebook));
        if (err < 0) {
            s->num_mvs = 0;
            return err;
        }
        s->num_mvs = num_mvs;
    }

    if (num_blocks_packed > s->num_blocks_packed) {
        int err;
        if ((err = av_reallocp(&s->block_codebook, num_blocks_packed * 16)) < 0) {
            s->num_blocks_packed = 0;
            return err;
        }
        s->num_blocks_packed = num_blocks_packed;
    }

    /* read motion vectors */
    mvbits = (num_mvs * 2 * 10 + 31) & ~31;

    if (buf_end - buf < (mvbits>>3) + 16*num_blocks_raw + 8*num_blocks_packed)
        return AVERROR_INVALIDDATA;

    init_get_bits(&gb, buf, mvbits);
    for (i = 0; i < num_mvs; i++) {
        s->mv_codebook[i][0] = get_sbits(&gb, 10);
        s->mv_codebook[i][1] = get_sbits(&gb, 10);
    }
    buf += mvbits >> 3;

    /* note ptr to uncompressed blocks */
    blocks_raw = buf;
    buf       += num_blocks_raw * 16;

    /* read compressed blocks */
    init_get_bits(&gb, buf, (buf_end - buf) << 3);
    for (i = 0; i < num_blocks_packed; i++) {
        int tmp[4];
        for (j = 0; j < 4; j++)
            tmp[j] = get_bits(&gb, 8);
        for (j = 0; j < 16; j++)
            s->block_codebook[i][15-j] = tmp[get_bits(&gb, 2)];
    }

    if (get_bits_left(&gb) < vector_bits *
        (s->avctx->height / 4) * (s->avctx->width / 4))
        return AVERROR_INVALIDDATA;

    /* read vectors and build frame */
    for (y = 0; y < s->avctx->height / 4; y++)
        for (x = 0; x < s->avctx->width / 4; x++) {
            unsigned int vector = get_bits(&gb, vector_bits);
            const uint8_t *src;
            ptrdiff_t src_stride;

            if (vector < num_mvs) {
                int mx = x * 4 + s->mv_codebook[vector][0];
                int my = y * 4 + s->mv_codebook[vector][1];

                if (mx < 0 || mx + 4 > s->avctx->width ||
                    my < 0 || my + 4 > s->avctx->height) {
                    av_log(s->avctx, AV_LOG_ERROR, "MV %d %d out of picture\n", mx, my);
                    continue;
                }

                src = s->last_frame->data[0] + mx + my * s->last_frame->linesize[0];
                src_stride = s->last_frame->linesize[0];
            } else {
                int offset = vector - num_mvs;
                if (offset < num_blocks_raw)
                    src = blocks_raw + 16*offset;
                else if (offset - num_blocks_raw < num_blocks_packed)
                    src = s->block_codebook[offset - num_blocks_raw];
                else
                    continue;
                src_stride = 4;
            }

            for (j = 0; j < 4; j++)
                for (i = 0; i < 4; i++)
                    frame->data[0][(y * 4 + j) * frame->linesize[0] + (x * 4 + i)] =
                        src[j * src_stride + i];
    }

    return 0;
}