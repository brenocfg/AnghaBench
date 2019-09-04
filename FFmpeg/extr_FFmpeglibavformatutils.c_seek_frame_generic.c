#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_25__ {int /*<<< orphan*/  pb; TYPE_3__* iformat; TYPE_1__* internal; TYPE_4__** streams; } ;
struct TYPE_24__ {scalar_t__ timestamp; int /*<<< orphan*/  pos; } ;
struct TYPE_23__ {int stream_index; scalar_t__ dts; int flags; } ;
struct TYPE_22__ {int nb_index_entries; TYPE_6__* index_entries; TYPE_2__* codecpar; } ;
struct TYPE_21__ {scalar_t__ (* read_seek ) (TYPE_7__*,int,scalar_t__,int) ;} ;
struct TYPE_20__ {scalar_t__ codec_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  data_offset; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVIndexEntry ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_CDGRAPHICS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_assert0 (TYPE_6__*) ; 
 int av_index_search_timestamp (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int av_read_frame (TYPE_7__*,TYPE_5__*) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_read_frame_flush (TYPE_7__*) ; 
 int /*<<< orphan*/  ff_update_cur_dts (TYPE_7__*,TYPE_4__*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_7__*,int,scalar_t__,int) ; 

__attribute__((used)) static int seek_frame_generic(AVFormatContext *s, int stream_index,
                              int64_t timestamp, int flags)
{
    int index;
    int64_t ret;
    AVStream *st;
    AVIndexEntry *ie;

    st = s->streams[stream_index];

    index = av_index_search_timestamp(st, timestamp, flags);

    if (index < 0 && st->nb_index_entries &&
        timestamp < st->index_entries[0].timestamp)
        return -1;

    if (index < 0 || index == st->nb_index_entries - 1) {
        AVPacket pkt;
        int nonkey = 0;

        if (st->nb_index_entries) {
            av_assert0(st->index_entries);
            ie = &st->index_entries[st->nb_index_entries - 1];
            if ((ret = avio_seek(s->pb, ie->pos, SEEK_SET)) < 0)
                return ret;
            ff_update_cur_dts(s, st, ie->timestamp);
        } else {
            if ((ret = avio_seek(s->pb, s->internal->data_offset, SEEK_SET)) < 0)
                return ret;
        }
        for (;;) {
            int read_status;
            do {
                read_status = av_read_frame(s, &pkt);
            } while (read_status == AVERROR(EAGAIN));
            if (read_status < 0)
                break;
            if (stream_index == pkt.stream_index && pkt.dts > timestamp) {
                if (pkt.flags & AV_PKT_FLAG_KEY) {
                    av_packet_unref(&pkt);
                    break;
                }
                if (nonkey++ > 1000 && st->codecpar->codec_id != AV_CODEC_ID_CDGRAPHICS) {
                    av_log(s, AV_LOG_ERROR,"seek_frame_generic failed as this stream seems to contain no keyframes after the target timestamp, %d non keyframes found\n", nonkey);
                    av_packet_unref(&pkt);
                    break;
                }
            }
            av_packet_unref(&pkt);
        }
        index = av_index_search_timestamp(st, timestamp, flags);
    }
    if (index < 0)
        return -1;

    ff_read_frame_flush(s);
    if (s->iformat->read_seek)
        if (s->iformat->read_seek(s, stream_index, timestamp, flags) >= 0)
            return 0;
    ie = &st->index_entries[index];
    if ((ret = avio_seek(s->pb, ie->pos, SEEK_SET)) < 0)
        return ret;
    ff_update_cur_dts(s, st, ie->timestamp);

    return 0;
}