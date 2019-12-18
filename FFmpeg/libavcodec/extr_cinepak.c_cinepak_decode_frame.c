#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int palette_has_changed; int /*<<< orphan*/  const** data; } ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int size; TYPE_5__* frame; int /*<<< orphan*/  const* pal; scalar_t__ palette_video; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_1__ CinepakContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int av_frame_ref (void*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int cinepak_decode (TYPE_1__*) ; 
 int cinepak_predecode_check (TYPE_1__*) ; 
 int ff_reget_buffer (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int cinepak_decode_frame(AVCodecContext *avctx,
                                void *data, int *got_frame,
                                AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int ret = 0, buf_size = avpkt->size;
    CinepakContext *s = avctx->priv_data;
    int num_strips;

    s->data = buf;
    s->size = buf_size;

    if (s->size < 10)
        return AVERROR_INVALIDDATA;

    num_strips = AV_RB16 (&s->data[8]);

    //Empty frame, do not waste time
    if (!num_strips && (!s->palette_video || !av_packet_get_side_data(avpkt, AV_PKT_DATA_PALETTE, NULL)))
        return buf_size;

    if ((ret = cinepak_predecode_check(s)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "cinepak_predecode_check failed\n");
        return ret;
    }

    if ((ret = ff_reget_buffer(avctx, s->frame, 0)) < 0)
        return ret;

    if (s->palette_video) {
        int size;
        const uint8_t *pal = av_packet_get_side_data(avpkt, AV_PKT_DATA_PALETTE, &size);
        if (pal && size == AVPALETTE_SIZE) {
            s->frame->palette_has_changed = 1;
            memcpy(s->pal, pal, AVPALETTE_SIZE);
        } else if (pal) {
            av_log(avctx, AV_LOG_ERROR, "Palette size %d is wrong\n", size);
        }
    }

    if ((ret = cinepak_decode(s)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "cinepak_decode failed\n");
    }

    if (s->palette_video)
        memcpy (s->frame->data[1], s->pal, AVPALETTE_SIZE);

    if ((ret = av_frame_ref(data, s->frame)) < 0)
        return ret;

    *got_frame = 1;

    /* report that the buffer was completely consumed */
    return buf_size;
}