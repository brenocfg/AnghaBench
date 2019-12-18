#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int* scratch_buffer; int buffer_size; int* y_buffer; TYPE_1__* pic; int /*<<< orphan*/  gb; } ;
typedef  TYPE_2__ XanContext ;
struct TYPE_11__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int** data; int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 unsigned int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned int bytestream2_size (int /*<<< orphan*/ *) ; 
 int xan_decode_chroma (TYPE_3__*,unsigned int) ; 
 int xan_unpack (TYPE_2__*,int*,int) ; 
 int xan_unpack_luma (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int xan_decode_frame_type0(AVCodecContext *avctx)
{
    XanContext *s = avctx->priv_data;
    uint8_t *ybuf, *prev_buf, *src = s->scratch_buffer;
    unsigned  chroma_off, corr_off;
    int cur, last;
    int i, j;
    int ret;

    chroma_off = bytestream2_get_le32(&s->gb);
    corr_off   = bytestream2_get_le32(&s->gb);

    if ((ret = xan_decode_chroma(avctx, chroma_off)) != 0)
        return ret;

    if (corr_off >= bytestream2_size(&s->gb)) {
        av_log(avctx, AV_LOG_WARNING, "Ignoring invalid correction block position\n");
        corr_off = 0;
    }
    bytestream2_seek(&s->gb, 12, SEEK_SET);
    ret = xan_unpack_luma(s, src, s->buffer_size >> 1);
    if (ret) {
        av_log(avctx, AV_LOG_ERROR, "Luma decoding failed\n");
        return ret;
    }

    ybuf = s->y_buffer;
    last = *src++;
    ybuf[0] = last << 1;
    for (j = 1; j < avctx->width - 1; j += 2) {
        cur = (last + *src++) & 0x1F;
        ybuf[j]   = last + cur;
        ybuf[j+1] = cur << 1;
        last = cur;
    }
    ybuf[j]  = last << 1;
    prev_buf = ybuf;
    ybuf += avctx->width;

    for (i = 1; i < avctx->height; i++) {
        last = ((prev_buf[0] >> 1) + *src++) & 0x1F;
        ybuf[0] = last << 1;
        for (j = 1; j < avctx->width - 1; j += 2) {
            cur = ((prev_buf[j + 1] >> 1) + *src++) & 0x1F;
            ybuf[j]   = last + cur;
            ybuf[j+1] = cur << 1;
            last = cur;
        }
        ybuf[j] = last << 1;
        prev_buf = ybuf;
        ybuf += avctx->width;
    }

    if (corr_off) {
        int dec_size;

        bytestream2_seek(&s->gb, 8 + corr_off, SEEK_SET);
        dec_size = xan_unpack(s, s->scratch_buffer, s->buffer_size / 2);
        if (dec_size < 0)
            dec_size = 0;
        else
            dec_size = FFMIN(dec_size, s->buffer_size/2 - 1);

        for (i = 0; i < dec_size; i++)
            s->y_buffer[i*2+1] = (s->y_buffer[i*2+1] + (s->scratch_buffer[i] << 1)) & 0x3F;
    }

    src  = s->y_buffer;
    ybuf = s->pic->data[0];
    for (j = 0; j < avctx->height; j++) {
        for (i = 0; i < avctx->width; i++)
            ybuf[i] = (src[i] << 2) | (src[i] >> 3);
        src  += avctx->width;
        ybuf += s->pic->linesize[0];
    }

    return 0;
}