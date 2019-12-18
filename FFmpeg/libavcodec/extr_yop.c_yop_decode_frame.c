#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int num_pal_colors; int dstbuf; int dstptr; int* srcptr; int* src_end; int* first_color; TYPE_3__* frame; int /*<<< orphan*/ * low_nibble; } ;
typedef  TYPE_1__ YopDecContext ;
struct TYPE_17__ {int height; int width; int /*<<< orphan*/  frame_number; TYPE_1__* priv_data; } ;
struct TYPE_16__ {int* data; int palette_has_changed; int* linesize; } ;
struct TYPE_15__ {int size; int* data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_frame_ref (void*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_reget_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yop_copy_previous_block (TYPE_1__*,int,int) ; 
 int yop_get_next_nibble (TYPE_1__*) ; 
 int yop_paint_block (TYPE_1__*,int,int) ; 

__attribute__((used)) static int yop_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                            AVPacket *avpkt)
{
    YopDecContext *s = avctx->priv_data;
    AVFrame *frame = s->frame;
    int tag, firstcolor, is_odd_frame;
    int ret, i, x, y;
    uint32_t *palette;

    if (avpkt->size < 4 + 3 * s->num_pal_colors) {
        av_log(avctx, AV_LOG_ERROR, "Packet too small.\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_reget_buffer(avctx, frame, 0)) < 0)
        return ret;

    if (!avctx->frame_number)
        memset(frame->data[1], 0, AVPALETTE_SIZE);

    s->dstbuf     = frame->data[0];
    s->dstptr     = frame->data[0];
    s->srcptr     = avpkt->data + 4;
    s->src_end    = avpkt->data + avpkt->size;
    s->low_nibble = NULL;

    is_odd_frame = avpkt->data[0];
    if(is_odd_frame>1){
        av_log(avctx, AV_LOG_ERROR, "frame is too odd %d\n", is_odd_frame);
        return AVERROR_INVALIDDATA;
    }
    firstcolor   = s->first_color[is_odd_frame];
    palette      = (uint32_t *)frame->data[1];

    for (i = 0; i < s->num_pal_colors; i++, s->srcptr += 3) {
        palette[i + firstcolor] = (s->srcptr[0] << 18) |
                                  (s->srcptr[1] << 10) |
                                  (s->srcptr[2] << 2);
        palette[i + firstcolor] |= 0xFFU << 24 |
                                   (palette[i + firstcolor] >> 6) & 0x30303;
    }

    frame->palette_has_changed = 1;

    for (y = 0; y < avctx->height; y += 2) {
        for (x = 0; x < avctx->width; x += 2) {
            if (s->srcptr - avpkt->data >= avpkt->size) {
                av_log(avctx, AV_LOG_ERROR, "Packet too small.\n");
                return AVERROR_INVALIDDATA;
            }

            tag = yop_get_next_nibble(s);

            if (tag != 0xf) {
                ret = yop_paint_block(s, frame->linesize[0], tag);
                if (ret < 0)
                    return ret;
            } else {
                tag = yop_get_next_nibble(s);
                ret = yop_copy_previous_block(s, frame->linesize[0], tag);
                if (ret < 0)
                    return ret;
            }
            s->dstptr += 2;
        }
        s->dstptr += 2*frame->linesize[0] - x;
    }

    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;

    *got_frame = 1;
    return avpkt->size;
}