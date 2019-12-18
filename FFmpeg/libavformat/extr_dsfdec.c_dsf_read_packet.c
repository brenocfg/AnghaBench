#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {TYPE_1__* internal; TYPE_4__** streams; int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_15__ {int duration; scalar_t__ pts; scalar_t__ stream_index; scalar_t__ pos; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {TYPE_2__* codecpar; } ;
struct TYPE_13__ {scalar_t__ data_end; scalar_t__ data_size; scalar_t__ audio_size; } ;
struct TYPE_12__ {int block_align; int channels; } ;
struct TYPE_11__ {scalar_t__ data_offset; } ;
typedef  TYPE_3__ DSFContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,int) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_new_packet (TYPE_5__*,scalar_t__) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsf_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    DSFContext *dsf = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[0];
    int64_t pos = avio_tell(pb);
    int ret;

    if (pos >= dsf->data_end)
        return AVERROR_EOF;

    if (dsf->data_size > dsf->audio_size) {
        int last_packet = pos == (dsf->data_end - st->codecpar->block_align);

        if (last_packet) {
            int64_t data_pos = pos - s->internal->data_offset;
            int64_t packet_size = dsf->audio_size - data_pos;
            int64_t skip_size = dsf->data_size - data_pos - packet_size;
            uint8_t *dst;
            int ch, ret;

            if (packet_size <= 0 || skip_size <= 0)
                return AVERROR_INVALIDDATA;

            if (av_new_packet(pkt, packet_size) < 0)
                return AVERROR(ENOMEM);
            dst = pkt->data;
            for (ch = 0; ch < st->codecpar->channels; ch++) {
                ret = avio_read(pb, dst,  packet_size / st->codecpar->channels);
                if (ret < packet_size / st->codecpar->channels)
                    return AVERROR_EOF;

                dst += ret;
                avio_skip(pb, skip_size / st->codecpar->channels);
            }

            pkt->pos = pos;
            pkt->stream_index = 0;
            pkt->pts = (pos - s->internal->data_offset) / st->codecpar->channels;
            pkt->duration = packet_size / st->codecpar->channels;
            return 0;
        }
    }
    ret = av_get_packet(pb, pkt, FFMIN(dsf->data_end - pos, st->codecpar->block_align));
    if (ret < 0)
        return ret;

    pkt->stream_index = 0;
    pkt->pts = (pos - s->internal->data_offset) / st->codecpar->channels;
    pkt->duration = st->codecpar->block_align / st->codecpar->channels;

    return 0;
}