#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_20__ {int current_audio_subpacket; int n_audio_subpackets; size_t current_sb; int audio_sample; size_t current_sb_entry; size_t n_sb_entries; int n_sb_blocks; TYPE_5__* sb_blocks; scalar_t__ sb_offset; TYPE_4__* audio_subpackets; TYPE_3__* sb_entries; int /*<<< orphan*/ * sb_pb; } ;
typedef  TYPE_6__ VividasDemuxContext ;
struct TYPE_23__ {TYPE_7__** streams; TYPE_6__* priv_data; } ;
struct TYPE_22__ {int stream_index; int pts; int* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_21__ {TYPE_2__* codecpar; TYPE_1__ time_base; } ;
struct TYPE_19__ {int packet_offset; scalar_t__ byte_offset; } ;
struct TYPE_18__ {int start; int pcm_bytes; } ;
struct TYPE_17__ {scalar_t__ flag; scalar_t__ size; } ;
struct TYPE_16__ {int sample_rate; int channels; } ;
typedef  TYPE_7__ AVStream ;
typedef  TYPE_8__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_9__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int INT_MAX ; 
 int MAX_AUDIO_SUBPACKETS ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_8__*,int) ; 
 int av_rescale (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int ffio_read_varlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_sb_block (TYPE_9__*,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viv_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    VividasDemuxContext *viv = s->priv_data;
    AVIOContext *pb;
    int64_t off;
    int ret;

    if (!viv->sb_pb)
        return AVERROR(EIO);
    if (avio_feof(viv->sb_pb))
        return AVERROR_EOF;

    if (viv->current_audio_subpacket < viv->n_audio_subpackets) {
        AVStream *astream;
        int size = viv->audio_subpackets[viv->current_audio_subpacket+1].start - viv->audio_subpackets[viv->current_audio_subpacket].start;

        pb = viv->sb_pb;
        ret = av_get_packet(pb, pkt, size);
        if (ret < 0)
            return ret;
        pkt->pos += viv->sb_offset + viv->sb_blocks[viv->current_sb].byte_offset;

        pkt->stream_index = 1;
        astream = s->streams[pkt->stream_index];

        pkt->pts = av_rescale(viv->audio_sample, astream->time_base.den, astream->time_base.num) / astream->codecpar->sample_rate;
        viv->audio_sample += viv->audio_subpackets[viv->current_audio_subpacket].pcm_bytes / 2 / astream->codecpar->channels;
        pkt->flags |= AV_PKT_FLAG_KEY;
        viv->current_audio_subpacket++;
        return 0;
    }

    if (viv->current_sb_entry >= viv->n_sb_entries) {
        if (viv->current_sb+1 >= viv->n_sb_blocks)
            return AVERROR(EIO);
        viv->current_sb++;

        load_sb_block(s, viv, 0);
        viv->current_sb_entry = 0;
    }

    pb = viv->sb_pb;
    if (!pb)
        return AVERROR(EIO);
    off = avio_tell(pb);
    off += viv->sb_entries[viv->current_sb_entry].size;

    if (viv->sb_entries[viv->current_sb_entry].flag == 0) {
        uint64_t v_size = ffio_read_varlen(pb);

        ffio_read_varlen(pb);
        if (v_size > INT_MAX)
            return AVERROR_INVALIDDATA;
        ret = av_get_packet(pb, pkt, v_size);
        if (ret < 0)
            return ret;
        pkt->pos += viv->sb_offset + viv->sb_blocks[viv->current_sb].byte_offset;

        pkt->pts = viv->sb_blocks[viv->current_sb].packet_offset + viv->current_sb_entry;
        pkt->flags |= (pkt->data[0]&0x80)?0:AV_PKT_FLAG_KEY;
        pkt->stream_index = 0;

        for (int i = 0; i < MAX_AUDIO_SUBPACKETS - 1; i++) {
            int start, pcm_bytes;
            start = ffio_read_varlen(pb);
            pcm_bytes = ffio_read_varlen(pb);

            if (i > 0 && start == 0)
                break;

            viv->n_audio_subpackets = i + 1;
            viv->audio_subpackets[i].start = start;
            viv->audio_subpackets[i].pcm_bytes = pcm_bytes;
        }
        viv->audio_subpackets[viv->n_audio_subpackets].start = (int)(off - avio_tell(pb));
        viv->current_audio_subpacket = 0;

    } else {
        uint64_t v_size = ffio_read_varlen(pb);

        if (v_size > INT_MAX)
            return AVERROR_INVALIDDATA;
        ret = av_get_packet(pb, pkt, v_size);
        if (ret < 0)
            return ret;
        pkt->pos += viv->sb_offset + viv->sb_blocks[viv->current_sb].byte_offset;
        pkt->pts = viv->sb_blocks[viv->current_sb].packet_offset + viv->current_sb_entry;
        pkt->flags |= (pkt->data[0] & 0x80) ? 0 : AV_PKT_FLAG_KEY;
        pkt->stream_index = 0;
    }

    viv->current_sb_entry++;

    return 0;
}