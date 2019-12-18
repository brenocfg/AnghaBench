#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int palette_has_changed; } ;
struct TYPE_16__ {TYPE_2__* priv_data; } ;
struct TYPE_15__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {TYPE_9__* frame; int /*<<< orphan*/  pal; int /*<<< orphan*/  gb; TYPE_1__* avctx; } ;
struct TYPE_13__ {int width; int height; } ;
typedef  TYPE_2__ SmcContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int av_frame_ref (void*,TYPE_9__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int ff_reget_buffer (TYPE_4__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  smc_decode_stream (TYPE_2__*) ; 

__attribute__((used)) static int smc_decode_frame(AVCodecContext *avctx,
                             void *data, int *got_frame,
                             AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    SmcContext *s = avctx->priv_data;
    int pal_size;
    const uint8_t *pal = av_packet_get_side_data(avpkt, AV_PKT_DATA_PALETTE, &pal_size);
    int ret;
    int total_blocks = ((s->avctx->width + 3) / 4) * ((s->avctx->height + 3) / 4);

    if (total_blocks / 1024 > avpkt->size)
        return AVERROR_INVALIDDATA;

    bytestream2_init(&s->gb, buf, buf_size);

    if ((ret = ff_reget_buffer(avctx, s->frame, 0)) < 0)
        return ret;

    if (pal && pal_size == AVPALETTE_SIZE) {
        s->frame->palette_has_changed = 1;
        memcpy(s->pal, pal, AVPALETTE_SIZE);
    } else if (pal) {
        av_log(avctx, AV_LOG_ERROR, "Palette size %d is wrong\n", pal_size);
    }

    smc_decode_stream(s);

    *got_frame      = 1;
    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;

    /* always report that the buffer was completely consumed */
    return buf_size;
}