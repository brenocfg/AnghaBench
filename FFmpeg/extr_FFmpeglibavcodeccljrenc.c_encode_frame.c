#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  luma_tmp ;
struct TYPE_14__ {int frame_number; int width; scalar_t__ strict_std_compliance; int height; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int** data; int* linesize; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int dither_type; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ CLJRContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXPERIMENTAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 scalar_t__ FF_COMPLIANCE_UNOFFICIAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *p, int *got_packet)
{
    CLJRContext *a = avctx->priv_data;
    PutBitContext pb;
    int x, y, ret;
    uint32_t dither= avctx->frame_number;
    static const uint32_t ordered_dither[2][2] =
    {
        { 0x10400000, 0x104F0000 },
        { 0xCB2A0000, 0xCB250000 },
    };

    if (avctx->width%4 && avctx->strict_std_compliance > FF_COMPLIANCE_UNOFFICIAL) {
         av_log(avctx, AV_LOG_ERROR,
                "Widths which are not a multiple of 4 might fail with some decoders, "
                "use vstrict=-1 / -strict -1 to use %d anyway.\n", avctx->width);
         return AVERROR_EXPERIMENTAL;
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, 32*avctx->height*avctx->width/4, 0)) < 0)
        return ret;

    init_put_bits(&pb, pkt->data, pkt->size);

    for (y = 0; y < avctx->height; y++) {
        uint8_t *luma = &p->data[0][y * p->linesize[0]];
        uint8_t *cb   = &p->data[1][y * p->linesize[1]];
        uint8_t *cr   = &p->data[2][y * p->linesize[2]];
        uint8_t luma_tmp[4];
        for (x = 0; x < avctx->width; x += 4) {
            switch (a->dither_type) {
            case 0: dither = 0x492A0000;                       break;
            case 1: dither = dither * 1664525 + 1013904223;    break;
            case 2: dither = ordered_dither[ y&1 ][ (x>>2)&1 ];break;
            }
            if (x+3 >= avctx->width) {
                memset(luma_tmp, 0, sizeof(luma_tmp));
                memcpy(luma_tmp, luma, avctx->width - x);
                luma = luma_tmp;
            }
            put_bits(&pb, 5, (249*(luma[3] +  (dither>>29)   )) >> 11);
            put_bits(&pb, 5, (249*(luma[2] + ((dither>>26)&7))) >> 11);
            put_bits(&pb, 5, (249*(luma[1] + ((dither>>23)&7))) >> 11);
            put_bits(&pb, 5, (249*(luma[0] + ((dither>>20)&7))) >> 11);
            luma += 4;
            put_bits(&pb, 6, (253*(*(cb++) + ((dither>>18)&3))) >> 10);
            put_bits(&pb, 6, (253*(*(cr++) + ((dither>>16)&3))) >> 10);
        }
    }

    flush_put_bits(&pb);

    pkt->size   = put_bits_count(&pb) / 8;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}