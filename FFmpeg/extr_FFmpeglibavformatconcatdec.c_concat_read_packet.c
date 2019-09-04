#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_27__ {TYPE_3__* priv_data; } ;
struct TYPE_26__ {size_t stream_index; scalar_t__ pts; scalar_t__ dts; } ;
struct TYPE_25__ {scalar_t__ cur_dts; int /*<<< orphan*/  time_base; } ;
struct TYPE_24__ {TYPE_1__* cur_file; TYPE_16__* avf; TYPE_1__* files; scalar_t__ eof; } ;
struct TYPE_23__ {size_t out_stream_index; } ;
struct TYPE_22__ {scalar_t__ start_time; scalar_t__ file_inpoint; scalar_t__ duration; scalar_t__ next_dts; int /*<<< orphan*/  metadata; TYPE_2__* streams; } ;
struct TYPE_21__ {TYPE_4__** streams; } ;
typedef  TYPE_2__ ConcatStream ;
typedef  TYPE_3__ ConcatContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_DATA_STRINGS_METADATA ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,unsigned int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 char* av_packet_pack_dictionary (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int av_read_frame (TYPE_16__*,TYPE_5__*) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_ts2str (scalar_t__) ; 
 int /*<<< orphan*/  av_ts2timestr (scalar_t__,int /*<<< orphan*/ *) ; 
 int filter_packet (TYPE_6__*,TYPE_2__*,TYPE_5__*) ; 
 int match_streams (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int open_next_file (TYPE_6__*) ; 
 scalar_t__ packet_after_outpoint (TYPE_3__*,TYPE_5__*) ; 

__attribute__((used)) static int concat_read_packet(AVFormatContext *avf, AVPacket *pkt)
{
    ConcatContext *cat = avf->priv_data;
    int ret;
    int64_t delta;
    ConcatStream *cs;
    AVStream *st;

    if (cat->eof)
        return AVERROR_EOF;

    if (!cat->avf)
        return AVERROR(EIO);

    while (1) {
        ret = av_read_frame(cat->avf, pkt);
        if (ret == AVERROR_EOF) {
            if ((ret = open_next_file(avf)) < 0)
                return ret;
            continue;
        }
        if (ret < 0)
            return ret;
        if ((ret = match_streams(avf)) < 0) {
            av_packet_unref(pkt);
            return ret;
        }
        if (packet_after_outpoint(cat, pkt)) {
            av_packet_unref(pkt);
            if ((ret = open_next_file(avf)) < 0)
                return ret;
            continue;
        }
        cs = &cat->cur_file->streams[pkt->stream_index];
        if (cs->out_stream_index < 0) {
            av_packet_unref(pkt);
            continue;
        }
        break;
    }
    if ((ret = filter_packet(avf, cs, pkt)))
        return ret;

    st = cat->avf->streams[pkt->stream_index];
    av_log(avf, AV_LOG_DEBUG, "file:%d stream:%d pts:%s pts_time:%s dts:%s dts_time:%s",
           (unsigned)(cat->cur_file - cat->files), pkt->stream_index,
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, &st->time_base));

    delta = av_rescale_q(cat->cur_file->start_time - cat->cur_file->file_inpoint,
                         AV_TIME_BASE_Q,
                         cat->avf->streams[pkt->stream_index]->time_base);
    if (pkt->pts != AV_NOPTS_VALUE)
        pkt->pts += delta;
    if (pkt->dts != AV_NOPTS_VALUE)
        pkt->dts += delta;
    av_log(avf, AV_LOG_DEBUG, " -> pts:%s pts_time:%s dts:%s dts_time:%s\n",
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, &st->time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, &st->time_base));
    if (cat->cur_file->metadata) {
        uint8_t* metadata;
        int metadata_len;
        char* packed_metadata = av_packet_pack_dictionary(cat->cur_file->metadata, &metadata_len);
        if (!packed_metadata)
            return AVERROR(ENOMEM);
        if (!(metadata = av_packet_new_side_data(pkt, AV_PKT_DATA_STRINGS_METADATA, metadata_len))) {
            av_freep(&packed_metadata);
            return AVERROR(ENOMEM);
        }
        memcpy(metadata, packed_metadata, metadata_len);
        av_freep(&packed_metadata);
    }

    if (cat->cur_file->duration == AV_NOPTS_VALUE && st->cur_dts != AV_NOPTS_VALUE) {
        int64_t next_dts = av_rescale_q(st->cur_dts, st->time_base, AV_TIME_BASE_Q);
        if (cat->cur_file->next_dts == AV_NOPTS_VALUE || next_dts > cat->cur_file->next_dts) {
            cat->cur_file->next_dts = next_dts;
        }
    }

    pkt->stream_index = cs->out_stream_index;
    return ret;
}