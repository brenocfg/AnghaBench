#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_18__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  pos; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int /*<<< orphan*/  index; TYPE_1__* codecpar; } ;
struct TYPE_16__ {int /*<<< orphan*/  queue_end; int /*<<< orphan*/  queue; int /*<<< orphan*/  ctx; } ;
struct TYPE_14__ {int sub_packet_size; int coded_framesize; int sub_packet_h; int sub_packet_cnt; int frame_size; int pkt_cnt; int /*<<< orphan*/  buf_timecode; int /*<<< orphan*/ * buf; } ;
struct TYPE_15__ {TYPE_2__ audio; } ;
struct TYPE_13__ {int block_align; scalar_t__ codec_id; } ;
typedef  TYPE_3__ MatroskaTrack ;
typedef  TYPE_4__ MatroskaDemuxContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_RA_288 ; 
 scalar_t__ AV_CODEC_ID_SIPR ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int av_new_packet (TYPE_6__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 int ff_packet_list_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_rm_reorder_sipr_data (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int matroska_parse_rm_audio(MatroskaDemuxContext *matroska,
                                   MatroskaTrack *track, AVStream *st,
                                   uint8_t *data, int size, uint64_t timecode,
                                   int64_t pos)
{
    int a = st->codecpar->block_align;
    int sps = track->audio.sub_packet_size;
    int cfs = track->audio.coded_framesize;
    int h   = track->audio.sub_packet_h;
    int y   = track->audio.sub_packet_cnt;
    int w   = track->audio.frame_size;
    int x;

    if (!track->audio.pkt_cnt) {
        if (track->audio.sub_packet_cnt == 0)
            track->audio.buf_timecode = timecode;
        if (st->codecpar->codec_id == AV_CODEC_ID_RA_288) {
            if (size < cfs * h / 2) {
                av_log(matroska->ctx, AV_LOG_ERROR,
                       "Corrupt int4 RM-style audio packet size\n");
                return AVERROR_INVALIDDATA;
            }
            for (x = 0; x < h / 2; x++)
                memcpy(track->audio.buf + x * 2 * w + y * cfs,
                       data + x * cfs, cfs);
        } else if (st->codecpar->codec_id == AV_CODEC_ID_SIPR) {
            if (size < w) {
                av_log(matroska->ctx, AV_LOG_ERROR,
                       "Corrupt sipr RM-style audio packet size\n");
                return AVERROR_INVALIDDATA;
            }
            memcpy(track->audio.buf + y * w, data, w);
        } else {
            if (size < sps * w / sps || h<=0 || w%sps) {
                av_log(matroska->ctx, AV_LOG_ERROR,
                       "Corrupt generic RM-style audio packet size\n");
                return AVERROR_INVALIDDATA;
            }
            for (x = 0; x < w / sps; x++)
                memcpy(track->audio.buf +
                       sps * (h * x + ((h + 1) / 2) * (y & 1) + (y >> 1)),
                       data + x * sps, sps);
        }

        if (++track->audio.sub_packet_cnt >= h) {
            if (st->codecpar->codec_id == AV_CODEC_ID_SIPR)
                ff_rm_reorder_sipr_data(track->audio.buf, h, w);
            track->audio.sub_packet_cnt = 0;
            track->audio.pkt_cnt        = h * w / a;
        }
    }

    while (track->audio.pkt_cnt) {
        int ret;
        AVPacket pktl, *pkt = &pktl;

        ret = av_new_packet(pkt, a);
        if (ret < 0) {
            return ret;
        }
        memcpy(pkt->data,
               track->audio.buf + a * (h * w / a - track->audio.pkt_cnt--),
               a);
        pkt->pts                  = track->audio.buf_timecode;
        track->audio.buf_timecode = AV_NOPTS_VALUE;
        pkt->pos                  = pos;
        pkt->stream_index         = st->index;
        ret = ff_packet_list_put(&matroska->queue, &matroska->queue_end, pkt, 0);
        if (ret < 0) {
            av_packet_unref(pkt);
            return AVERROR(ENOMEM);
        }
    }

    return 0;
}