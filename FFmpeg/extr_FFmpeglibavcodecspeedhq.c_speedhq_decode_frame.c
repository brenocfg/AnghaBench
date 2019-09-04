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
struct TYPE_14__ {int /*<<< orphan*/  height; void* coded_height; int /*<<< orphan*/  width; void* coded_width; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int key_frame; } ;
struct TYPE_12__ {int* data; int size; } ;
struct TYPE_11__ {int /*<<< orphan*/  quant_matrix; } ;
typedef  TYPE_1__ SHQContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RL24 (int const*) ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  compute_quant_matrix (int /*<<< orphan*/ ,int) ; 
 int decode_speedhq_field (TYPE_1__* const,int const*,int,TYPE_3__*,int,int,int,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int speedhq_decode_frame(AVCodecContext *avctx,
                                void *data, int *got_frame,
                                AVPacket *avpkt)
{
    SHQContext * const s = avctx->priv_data;
    const uint8_t *buf   = avpkt->data;
    int buf_size         = avpkt->size;
    AVFrame *frame       = data;
    uint8_t quality;
    uint32_t second_field_offset;
    int ret;

    if (buf_size < 4)
        return AVERROR_INVALIDDATA;

    quality = buf[0];
    if (quality >= 100) {
        return AVERROR_INVALIDDATA;
    }

    compute_quant_matrix(s->quant_matrix, 100 - quality);

    second_field_offset = AV_RL24(buf + 1);
    if (second_field_offset >= buf_size - 3) {
        return AVERROR_INVALIDDATA;
    }

    avctx->coded_width = FFALIGN(avctx->width, 16);
    avctx->coded_height = FFALIGN(avctx->height, 16);

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0) {
        return ret;
    }
    frame->key_frame = 1;

    if (second_field_offset == 4) {
        /*
         * Overlapping first and second fields is used to signal
         * encoding only a single field. In this case, "height"
         * is ambiguous; it could mean either the height of the
         * frame as a whole, or of the field. The former would make
         * more sense for compatibility with legacy decoders,
         * but this matches the convention used in NDI, which is
         * the primary user of this trick.
         */
        if ((ret = decode_speedhq_field(s, buf, buf_size, frame, 0, 4, buf_size, 1)) < 0)
            return ret;
    } else {
        if ((ret = decode_speedhq_field(s, buf, buf_size, frame, 0, 4, second_field_offset, 2)) < 0)
            return ret;
        if ((ret = decode_speedhq_field(s, buf, buf_size, frame, 1, second_field_offset, buf_size, 2)) < 0)
            return ret;
    }

    *got_frame = 1;
    return buf_size;
}