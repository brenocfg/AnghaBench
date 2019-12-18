#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* bswap_buf ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_23__ {int mb_height; int mb_width; int mb_height2; int mb_width2; TYPE_1__ bbdsp; int /*<<< orphan*/  pb; int /*<<< orphan*/  block; } ;
struct TYPE_22__ {scalar_t__ codec_id; TYPE_5__* priv_data; } ;
struct TYPE_21__ {int width; int height; int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  format; } ;
struct TYPE_20__ {size_t* data; int size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ ASV1Context ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 scalar_t__ AV_CODEC_ID_ASV1 ; 
 scalar_t__ AV_INPUT_BUFFER_MIN_SIZE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int,int) ; 
 int MAX_MB_SIZE ; 
 TYPE_3__* av_frame_alloc () ; 
 int av_frame_copy (TYPE_3__*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int av_frame_get_buffer (TYPE_3__*,int) ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dct_get (TYPE_5__* const,TYPE_3__ const*,int,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  encode_mb (TYPE_5__* const,int /*<<< orphan*/ ) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t* ff_reverse ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pict, int *got_packet)
{
    ASV1Context *const a = avctx->priv_data;
    int size, ret;
    int mb_x, mb_y;

    if (pict->width % 16 || pict->height % 16) {
        AVFrame *clone = av_frame_alloc();
        int i;

        if (!clone)
            return AVERROR(ENOMEM);
        clone->format = pict->format;
        clone->width  = FFALIGN(pict->width, 16);
        clone->height = FFALIGN(pict->height, 16);
        ret = av_frame_get_buffer(clone, 32);
        if (ret < 0) {
            av_frame_free(&clone);
            return ret;
        }

        ret = av_frame_copy(clone, pict);
        if (ret < 0) {
            av_frame_free(&clone);
            return ret;
        }

        for (i = 0; i<3; i++) {
            int x, y;
            int w  = AV_CEIL_RSHIFT(pict->width, !!i);
            int h  = AV_CEIL_RSHIFT(pict->height, !!i);
            int w2 = AV_CEIL_RSHIFT(clone->width, !!i);
            int h2 = AV_CEIL_RSHIFT(clone->height, !!i);
            for (y=0; y<h; y++)
                for (x=w; x<w2; x++)
                    clone->data[i][x + y*clone->linesize[i]] =
                        clone->data[i][w - 1 + y*clone->linesize[i]];
            for (y=h; y<h2; y++)
                for (x=0; x<w2; x++)
                    clone->data[i][x + y*clone->linesize[i]] =
                        clone->data[i][x + (h-1)*clone->linesize[i]];
        }
        ret = encode_frame(avctx, pkt, clone, got_packet);

        av_frame_free(&clone);
        return ret;
    }

    if ((ret = ff_alloc_packet2(avctx, pkt, a->mb_height * a->mb_width * MAX_MB_SIZE +
                                AV_INPUT_BUFFER_MIN_SIZE, 0)) < 0)
        return ret;

    init_put_bits(&a->pb, pkt->data, pkt->size);

    for (mb_y = 0; mb_y < a->mb_height2; mb_y++) {
        for (mb_x = 0; mb_x < a->mb_width2; mb_x++) {
            dct_get(a, pict, mb_x, mb_y);
            encode_mb(a, a->block);
        }
    }

    if (a->mb_width2 != a->mb_width) {
        mb_x = a->mb_width2;
        for (mb_y = 0; mb_y < a->mb_height2; mb_y++) {
            dct_get(a, pict, mb_x, mb_y);
            encode_mb(a, a->block);
        }
    }

    if (a->mb_height2 != a->mb_height) {
        mb_y = a->mb_height2;
        for (mb_x = 0; mb_x < a->mb_width; mb_x++) {
            dct_get(a, pict, mb_x, mb_y);
            encode_mb(a, a->block);
        }
    }
    emms_c();

    avpriv_align_put_bits(&a->pb);
    while (put_bits_count(&a->pb) & 31)
        put_bits(&a->pb, 8, 0);

    size = put_bits_count(&a->pb) / 32;

    if (avctx->codec_id == AV_CODEC_ID_ASV1) {
        a->bbdsp.bswap_buf((uint32_t *) pkt->data,
                           (uint32_t *) pkt->data, size);
    } else {
        int i;
        for (i = 0; i < 4 * size; i++)
            pkt->data[i] = ff_reverse[pkt->data[i]];
    }

    pkt->size   = size * 4;
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}