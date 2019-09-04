#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int key_frame; int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int change_field_order; } ;
typedef  TYPE_1__ FRWUContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int MKTAG (float,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream_get_le32 (int /*<<< orphan*/  const**) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    FRWUContext *s = avctx->priv_data;
    int field, ret;
    AVFrame *pic = data;
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end = buf + avpkt->size;

    if (avpkt->size < avctx->width * 2 * avctx->height + 4 + 2*8) {
        av_log(avctx, AV_LOG_ERROR, "Packet is too small.\n");
        return AVERROR_INVALIDDATA;
    }
    if (bytestream_get_le32(&buf) != MKTAG('F', 'R', 'W', '1')) {
        av_log(avctx, AV_LOG_ERROR, "incorrect marker\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    pic->pict_type = AV_PICTURE_TYPE_I;
    pic->key_frame = 1;

    for (field = 0; field < 2; field++) {
        int i;
        int field_h = (avctx->height + !field) >> 1;
        int field_size, min_field_size = avctx->width * 2 * field_h;
        uint8_t *dst = pic->data[0];
        if (buf_end - buf < 8)
            return AVERROR_INVALIDDATA;
        buf += 4; // flags? 0x80 == bottom field maybe?
        field_size = bytestream_get_le32(&buf);
        if (field_size < min_field_size) {
            av_log(avctx, AV_LOG_ERROR, "Field size %i is too small (required %i)\n", field_size, min_field_size);
            return AVERROR_INVALIDDATA;
        }
        if (buf_end - buf < field_size) {
            av_log(avctx, AV_LOG_ERROR, "Packet is too small, need %i, have %i\n", field_size, (int)(buf_end - buf));
            return AVERROR_INVALIDDATA;
        }
        if (field ^ s->change_field_order) {
            dst += pic->linesize[0];
        } else if (s->change_field_order) {
            dst += 2 * pic->linesize[0];
        }
        for (i = 0; i < field_h; i++) {
            if (s->change_field_order && field && i == field_h - 1)
                dst = pic->data[0];
            memcpy(dst, buf, avctx->width * 2);
            buf += avctx->width * 2;
            dst += pic->linesize[0] << 1;
        }
        buf += field_size - min_field_size;
    }

    *got_frame = 1;

    return avpkt->size;
}