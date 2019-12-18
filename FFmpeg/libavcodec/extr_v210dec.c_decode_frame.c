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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int custom_stride; int stride_warning_shown; int aligned_input; int /*<<< orphan*/  (* unpack_frame ) (int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ V210DecContext ;
struct TYPE_14__ {int width; int height; scalar_t__ codec_tag; scalar_t__ field_order; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int key_frame; int* linesize; int interlaced_frame; int top_field_first; int /*<<< orphan*/  pict_type; scalar_t__* data; } ;
struct TYPE_12__ {char* data; int size; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_FIELD_PROGRESSIVE ; 
 scalar_t__ AV_FIELD_TB ; 
 scalar_t__ AV_FIELD_TT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_RN32 (char const*) ; 
 scalar_t__ MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_PIXELS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_le2ne32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_v210dec_init (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    V210DecContext *s = avctx->priv_data;

    int h, w, ret, stride, aligned_input;
    AVFrame *pic = data;
    const uint8_t *psrc = avpkt->data;
    uint16_t *y, *u, *v;

    if (s->custom_stride )
        stride = s->custom_stride;
    else {
        int aligned_width = ((avctx->width + 47) / 48) * 48;
        stride = aligned_width * 8 / 3;
    }

    if (avpkt->size < stride * avctx->height) {
        if ((((avctx->width + 23) / 24) * 24 * 8) / 3 * avctx->height == avpkt->size) {
            stride = avpkt->size / avctx->height;
            if (!s->stride_warning_shown)
                av_log(avctx, AV_LOG_WARNING, "Broken v210 with too small padding (64 byte) detected\n");
            s->stride_warning_shown = 1;
        } else {
            av_log(avctx, AV_LOG_ERROR, "packet too small\n");
            return AVERROR_INVALIDDATA;
        }
    }
    if (   avctx->codec_tag == MKTAG('C', '2', '1', '0')
        && avpkt->size > 64
        && AV_RN32(psrc) == AV_RN32("INFO")
        && avpkt->size - 64 >= stride * avctx->height)
        psrc += 64;

    aligned_input = !((uintptr_t)psrc & 0x1f) && !(stride & 0x1f);
    if (aligned_input != s->aligned_input) {
        s->aligned_input = aligned_input;
        ff_v210dec_init(s);
    }

    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    y = (uint16_t*)pic->data[0];
    u = (uint16_t*)pic->data[1];
    v = (uint16_t*)pic->data[2];
    pic->pict_type = AV_PICTURE_TYPE_I;
    pic->key_frame = 1;

    for (h = 0; h < avctx->height; h++) {
        const uint32_t *src = (const uint32_t*)psrc;
        uint32_t val;

        w = (avctx->width / 12) * 12;
        s->unpack_frame(src, y, u, v, w);

        y += w;
        u += w >> 1;
        v += w >> 1;
        src += (w << 1) / 3;

        if (w < avctx->width - 5) {
            READ_PIXELS(u, y, v);
            READ_PIXELS(y, u, y);
            READ_PIXELS(v, y, u);
            READ_PIXELS(y, v, y);
            w += 6;
        }

        if (w < avctx->width - 1) {
            READ_PIXELS(u, y, v);

            val  = av_le2ne32(*src++);
            *y++ =  val & 0x3FF;
            if (w < avctx->width - 3) {
                *u++ = (val >> 10) & 0x3FF;
                *y++ = (val >> 20) & 0x3FF;

                val  = av_le2ne32(*src++);
                *v++ =  val & 0x3FF;
                *y++ = (val >> 10) & 0x3FF;
            }
        }

        psrc += stride;
        y += pic->linesize[0] / 2 - avctx->width + (avctx->width & 1);
        u += pic->linesize[1] / 2 - avctx->width / 2;
        v += pic->linesize[2] / 2 - avctx->width / 2;
    }

    if (avctx->field_order > AV_FIELD_PROGRESSIVE) {
        /* we have interlaced material flagged in container */
        pic->interlaced_frame = 1;
        if (avctx->field_order == AV_FIELD_TT || avctx->field_order == AV_FIELD_TB)
            pic->top_field_first = 1;
    }

    *got_frame      = 1;

    return avpkt->size;
}