#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {int avail_in; int avail_out; int /*<<< orphan*/ * next_out; scalar_t__ next_in; } ;
struct FlashSVContext {int block_size; int diff_height; int image_height; int /*<<< orphan*/  pal; TYPE_2__* frame; TYPE_5__ zstream; int /*<<< orphan*/ * tmpblock; int /*<<< orphan*/  color_depth; scalar_t__ diff_start; TYPE_1__* blocks; scalar_t__ keyframedata; scalar_t__ is_keyframe; scalar_t__ zlibprime_prev; scalar_t__ zlibprime_curr; } ;
struct TYPE_14__ {struct FlashSVContext* priv_data; } ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {int* linesize; scalar_t__* data; } ;
struct TYPE_11__ {int size; scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int Z_DATA_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int decode_hybrid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int flashsv2_prime (struct FlashSVContext*,scalar_t__,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int inflate (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int inflateReset (TYPE_5__*) ; 
 int /*<<< orphan*/  inflateSync (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flashsv_decode_block(AVCodecContext *avctx, AVPacket *avpkt,
                                GetBitContext *gb, int block_size,
                                int width, int height, int x_pos, int y_pos,
                                int blk_idx)
{
    struct FlashSVContext *s = avctx->priv_data;
    uint8_t *line = s->tmpblock;
    int k;
    int ret = inflateReset(&s->zstream);
    if (ret != Z_OK) {
        av_log(avctx, AV_LOG_ERROR, "Inflate reset error: %d\n", ret);
        return AVERROR_UNKNOWN;
    }
    if (s->zlibprime_curr || s->zlibprime_prev) {
        ret = flashsv2_prime(s,
                             s->blocks[blk_idx].pos,
                             s->blocks[blk_idx].size);
        if (ret < 0)
            return ret;
    }
    s->zstream.next_in   = avpkt->data + get_bits_count(gb) / 8;
    s->zstream.avail_in  = block_size;
    s->zstream.next_out  = s->tmpblock;
    s->zstream.avail_out = s->block_size * 3;
    ret = inflate(&s->zstream, Z_FINISH);
    if (ret == Z_DATA_ERROR) {
        av_log(avctx, AV_LOG_ERROR, "Zlib resync occurred\n");
        inflateSync(&s->zstream);
        ret = inflate(&s->zstream, Z_FINISH);
    }

    if (ret != Z_OK && ret != Z_STREAM_END) {
        //return -1;
    }

    if (s->is_keyframe) {
        s->blocks[blk_idx].pos  = s->keyframedata + (get_bits_count(gb) / 8);
        s->blocks[blk_idx].size = block_size;
    }

    y_pos += s->diff_start;

    if (!s->color_depth) {
        /* Flash Screen Video stores the image upside down, so copy
         * lines to destination in reverse order. */
        for (k = 1; k <= s->diff_height; k++) {
            memcpy(s->frame->data[0] + x_pos * 3 +
                   (s->image_height - y_pos - k) * s->frame->linesize[0],
                   line, width * 3);
            /* advance source pointer to next line */
            line += width * 3;
        }
    } else {
        /* hybrid 15-bit/palette mode */
        ret = decode_hybrid(s->tmpblock, s->zstream.next_out,
                      s->frame->data[0],
                      s->image_height - (y_pos + 1 + s->diff_height),
                      x_pos, s->diff_height, width,
                      s->frame->linesize[0], s->pal);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "decode_hybrid failed\n");
            return ret;
        }
    }
    skip_bits_long(gb, 8 * block_size); /* skip the consumed bits */
    return 0;
}