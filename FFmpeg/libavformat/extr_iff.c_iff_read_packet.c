#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_15__ {TYPE_3__** streams; int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_14__ {int pos; scalar_t__ stream_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  duration; } ;
struct TYPE_13__ {TYPE_1__* codecpar; } ;
struct TYPE_12__ {int body_end; int body_size; int body_pos; } ;
struct TYPE_11__ {scalar_t__ codec_tag; scalar_t__ codec_type; int block_align; } ;
typedef  TYPE_2__ IffDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int FFMIN (int,int) ; 
 scalar_t__ ID_ANIM ; 
 scalar_t__ ID_DSD ; 
 scalar_t__ ID_DST ; 
 scalar_t__ ID_FORM ; 
 scalar_t__ ID_ILBM ; 
 scalar_t__ ID_MAUD ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_anim_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_dst_frame (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static int iff_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    IffDemuxContext *iff = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[0];
    int ret;
    int64_t pos = avio_tell(pb);

    if (avio_feof(pb))
        return AVERROR_EOF;
    if (st->codecpar->codec_tag != ID_ANIM && pos >= iff->body_end)
        return AVERROR_EOF;

    if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        if (st->codecpar->codec_tag == ID_DSD || st->codecpar->codec_tag == ID_MAUD) {
            ret = av_get_packet(pb, pkt, FFMIN(iff->body_end - pos, 1024 * st->codecpar->block_align));
        } else if (st->codecpar->codec_tag == ID_DST) {
            return read_dst_frame(s, pkt);
        } else {
            if (iff->body_size > INT_MAX)
                return AVERROR_INVALIDDATA;
            ret = av_get_packet(pb, pkt, iff->body_size);
        }
    } else if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO &&
               st->codecpar->codec_tag  == ID_ANIM) {
        uint64_t data_size, orig_pos;
        uint32_t chunk_id, chunk_id2;

        while (!avio_feof(pb)) {
            if (avio_feof(pb))
                return AVERROR_EOF;

            orig_pos  = avio_tell(pb);
            chunk_id  = avio_rl32(pb);
            data_size = avio_rb32(pb);
            chunk_id2 = avio_rl32(pb);

            if (chunk_id  == ID_FORM &&
                chunk_id2 == ID_ILBM) {
                avio_skip(pb, -4);
                break;
            } else if (chunk_id == ID_FORM &&
                       chunk_id2 == ID_ANIM) {
                continue;
            } else {
                avio_skip(pb, data_size);
            }
        }
        ret = av_get_packet(pb, pkt, data_size);
        pkt->pos = orig_pos;
        pkt->duration = get_anim_duration(pkt->data, pkt->size);
        if (pos == 12)
            pkt->flags |= AV_PKT_FLAG_KEY;
    } else if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO &&
               st->codecpar->codec_tag  != ID_ANIM) {
        ret = av_get_packet(pb, pkt, iff->body_size);
        pkt->pos = pos;
        if (pos == iff->body_pos)
            pkt->flags |= AV_PKT_FLAG_KEY;
    } else {
        av_assert0(0);
    }

    if (ret < 0)
        return ret;
    pkt->stream_index = 0;
    return ret;
}