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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_16__ {int size; int stream_index; int flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {TYPE_1__* tracks; } ;
struct TYPE_14__ {int /*<<< orphan*/  sample_queue; TYPE_4__* rtp_ctx; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  RTP_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_3__*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_mov_write_packet (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_write_chained (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ffio_open_dyn_packet_buf (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sample_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sample_queue_retain (int /*<<< orphan*/ *) ; 
 int write_hint_packets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *) ; 

int ff_mov_add_hinted_packet(AVFormatContext *s, AVPacket *pkt,
                             int track_index, int sample,
                             uint8_t *sample_data, int sample_size)
{
    MOVMuxContext *mov = s->priv_data;
    MOVTrack *trk = &mov->tracks[track_index];
    AVFormatContext *rtp_ctx = trk->rtp_ctx;
    uint8_t *buf = NULL;
    int size;
    AVIOContext *hintbuf = NULL;
    AVPacket hint_pkt;
    int ret = 0, count;

    if (!rtp_ctx)
        return AVERROR(ENOENT);
    if (!rtp_ctx->pb)
        return AVERROR(ENOMEM);

    if (sample_data)
        sample_queue_push(&trk->sample_queue, sample_data, sample_size, sample);
    else
        sample_queue_push(&trk->sample_queue, pkt->data, pkt->size, sample);

    /* Feed the packet to the RTP muxer */
    ff_write_chained(rtp_ctx, 0, pkt, s, 0);

    /* Fetch the output from the RTP muxer, open a new output buffer
     * for next time. */
    size = avio_close_dyn_buf(rtp_ctx->pb, &buf);
    if ((ret = ffio_open_dyn_packet_buf(&rtp_ctx->pb,
                                        RTP_MAX_PACKET_SIZE)) < 0)
        goto done;

    if (size <= 0)
        goto done;

    /* Open a buffer for writing the hint */
    if ((ret = avio_open_dyn_buf(&hintbuf)) < 0)
        goto done;
    av_init_packet(&hint_pkt);
    count = write_hint_packets(hintbuf, buf, size, trk, &hint_pkt.dts);
    av_freep(&buf);

    /* Write the hint data into the hint track */
    hint_pkt.size = size = avio_close_dyn_buf(hintbuf, &buf);
    hint_pkt.data = buf;
    hint_pkt.pts  = hint_pkt.dts;
    hint_pkt.stream_index = track_index;
    if (pkt->flags & AV_PKT_FLAG_KEY)
        hint_pkt.flags |= AV_PKT_FLAG_KEY;
    if (count > 0)
        ff_mov_write_packet(s, &hint_pkt);
done:
    av_free(buf);
    sample_queue_retain(&trk->sample_queue);
    return ret;
}