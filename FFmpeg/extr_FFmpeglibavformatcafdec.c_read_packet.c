#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {TYPE_2__* priv_data; TYPE_3__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_12__ {int size; int dts; int pts; scalar_t__ stream_index; } ;
struct TYPE_11__ {int nb_index_entries; int duration; TYPE_1__* index_entries; } ;
struct TYPE_10__ {scalar_t__ data_size; int data_start; int frames_per_packet; int bytes_per_packet; int packet_cnt; int num_bytes; int frame_cnt; } ;
struct TYPE_9__ {int pos; int timestamp; } ;
typedef  TYPE_2__ CafContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int CAF_MAX_PKT_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int FFMIN (int,int) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    AVStream *st      = s->streams[0];
    CafContext *caf   = s->priv_data;
    int res, pkt_size = 0, pkt_frames = 0;
    int64_t left      = CAF_MAX_PKT_SIZE;

    if (avio_feof(pb))
        return AVERROR_EOF;

    /* don't read past end of data chunk */
    if (caf->data_size > 0) {
        left = (caf->data_start + caf->data_size) - avio_tell(pb);
        if (!left)
            return AVERROR_EOF;
        if (left < 0)
            return AVERROR(EIO);
    }

    pkt_frames = caf->frames_per_packet;
    pkt_size   = caf->bytes_per_packet;

    if (pkt_size > 0 && pkt_frames == 1) {
        pkt_size   = (CAF_MAX_PKT_SIZE / pkt_size) * pkt_size;
        pkt_size   = FFMIN(pkt_size, left);
        pkt_frames = pkt_size / caf->bytes_per_packet;
    } else if (st->nb_index_entries) {
        if (caf->packet_cnt < st->nb_index_entries - 1) {
            pkt_size   = st->index_entries[caf->packet_cnt + 1].pos       - st->index_entries[caf->packet_cnt].pos;
            pkt_frames = st->index_entries[caf->packet_cnt + 1].timestamp - st->index_entries[caf->packet_cnt].timestamp;
        } else if (caf->packet_cnt == st->nb_index_entries - 1) {
            pkt_size   = caf->num_bytes - st->index_entries[caf->packet_cnt].pos;
            pkt_frames = st->duration   - st->index_entries[caf->packet_cnt].timestamp;
        } else {
            return AVERROR(EIO);
        }
    }

    if (pkt_size == 0 || pkt_frames == 0 || pkt_size > left)
        return AVERROR(EIO);

    res = av_get_packet(pb, pkt, pkt_size);
    if (res < 0)
        return res;

    pkt->size           = res;
    pkt->stream_index   = 0;
    pkt->dts = pkt->pts = caf->frame_cnt;

    caf->packet_cnt++;
    caf->frame_cnt += pkt_frames;

    return 0;
}