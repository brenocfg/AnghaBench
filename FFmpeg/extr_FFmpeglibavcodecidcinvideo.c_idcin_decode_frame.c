#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {TYPE_1__* priv_data; } ;
struct TYPE_15__ {int palette_has_changed; int /*<<< orphan*/  const** data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int size; int /*<<< orphan*/  const* pal; int /*<<< orphan*/  const* buf; } ;
typedef  TYPE_1__ IdcinContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ idcin_decode_vlcs (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int idcin_decode_frame(AVCodecContext *avctx,
                              void *data, int *got_frame,
                              AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    IdcinContext *s = avctx->priv_data;
    int pal_size;
    const uint8_t *pal = av_packet_get_side_data(avpkt, AV_PKT_DATA_PALETTE, &pal_size);
    AVFrame *frame = data;
    int ret;

    s->buf = buf;
    s->size = buf_size;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    if (idcin_decode_vlcs(s, frame))
        return AVERROR_INVALIDDATA;

    if (pal && pal_size == AVPALETTE_SIZE) {
        frame->palette_has_changed = 1;
        memcpy(s->pal, pal, AVPALETTE_SIZE);
    } else if (pal) {
        av_log(avctx, AV_LOG_ERROR, "Palette size %d is wrong\n", pal_size);
    }
    /* make the palette available on the way out */
    memcpy(frame->data[1], s->pal, AVPALETTE_SIZE);

    *got_frame = 1;

    /* report that the buffer was completely consumed */
    return buf_size;
}