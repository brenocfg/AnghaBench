#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_28__ {int /*<<< orphan*/  frame_number; TYPE_2__* priv_data; } ;
struct TYPE_27__ {int duration; int /*<<< orphan*/  pts; } ;
struct TYPE_21__ {int frames; int /*<<< orphan*/  framesize; } ;
struct TYPE_24__ {int /*<<< orphan*/  remaining_samples; } ;
struct TYPE_23__ {int available; } ;
struct TYPE_26__ {TYPE_10__ packet; TYPE_16__ afq; int /*<<< orphan*/ * rc; TYPE_11__* frame; int /*<<< orphan*/  psyctx; TYPE_13__ bufqueue; TYPE_1__* avctx; } ;
struct TYPE_25__ {int frame_size; } ;
struct TYPE_22__ {int framebits; } ;
typedef  TYPE_2__ OpusEncContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_SKIP_SAMPLES ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int OPUS_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  celt_encode_frame (TYPE_2__*,int /*<<< orphan*/ *,TYPE_11__*,int) ; 
 int ff_af_queue_add (TYPE_16__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ff_af_queue_remove (TYPE_16__*,int,int /*<<< orphan*/ *,int*) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_4__*,TYPE_13__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_opus_psy_postencode_update (int /*<<< orphan*/ *,TYPE_11__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_opus_psy_process (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  ff_opus_psy_signal_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opus_packet_assembler (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * spawn_empty_frame (TYPE_2__*) ; 

__attribute__((used)) static int opus_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                             const AVFrame *frame, int *got_packet_ptr)
{
    OpusEncContext *s = avctx->priv_data;
    int ret, frame_size, alloc_size = 0;

    if (frame) { /* Add new frame to queue */
        if ((ret = ff_af_queue_add(&s->afq, frame)) < 0)
            return ret;
        ff_bufqueue_add(avctx, &s->bufqueue, av_frame_clone(frame));
    } else {
        ff_opus_psy_signal_eof(&s->psyctx);
        if (!s->afq.remaining_samples || !avctx->frame_number)
            return 0; /* We've been flushed and there's nothing left to encode */
    }

    /* Run the psychoacoustic system */
    if (ff_opus_psy_process(&s->psyctx, &s->packet))
        return 0;

    frame_size = OPUS_BLOCK_SIZE(s->packet.framesize);

    if (!frame) {
        /* This can go negative, that's not a problem, we only pad if positive */
        int pad_empty = s->packet.frames*(frame_size/s->avctx->frame_size) - s->bufqueue.available + 1;
        /* Pad with empty 2.5 ms frames to whatever framesize was decided,
         * this should only happen at the very last flush frame. The frames
         * allocated here will be freed (because they have no other references)
         * after they get used by celt_frame_setup_input() */
        for (int i = 0; i < pad_empty; i++) {
            AVFrame *empty = spawn_empty_frame(s);
            if (!empty)
                return AVERROR(ENOMEM);
            ff_bufqueue_add(avctx, &s->bufqueue, empty);
        }
    }

    for (int i = 0; i < s->packet.frames; i++) {
        celt_encode_frame(s, &s->rc[i], &s->frame[i], i);
        alloc_size += s->frame[i].framebits >> 3;
    }

    /* Worst case toc + the frame lengths if needed */
    alloc_size += 2 + s->packet.frames*2;

    if ((ret = ff_alloc_packet2(avctx, avpkt, alloc_size, 0)) < 0)
        return ret;

    /* Assemble packet */
    opus_packet_assembler(s, avpkt);

    /* Update the psychoacoustic system */
    ff_opus_psy_postencode_update(&s->psyctx, s->frame, s->rc);

    /* Remove samples from queue and skip if needed */
    ff_af_queue_remove(&s->afq, s->packet.frames*frame_size, &avpkt->pts, &avpkt->duration);
    if (s->packet.frames*frame_size > avpkt->duration) {
        uint8_t *side = av_packet_new_side_data(avpkt, AV_PKT_DATA_SKIP_SAMPLES, 10);
        if (!side)
            return AVERROR(ENOMEM);
        AV_WL32(&side[4], s->packet.frames*frame_size - avpkt->duration + 120);
    }

    *got_packet_ptr = 1;

    return 0;
}