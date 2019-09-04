#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {size_t nb_streams; TYPE_2__** streams; TYPE_5__* pb; TYPE_1__* priv_data; } ;
struct TYPE_18__ {int seekable; } ;
struct TYPE_17__ {scalar_t__ pos; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  size; } ;
struct TYPE_16__ {size_t stream_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  pts; } ;
struct TYPE_15__ {int nb_index_entries; TYPE_4__* index_entries; } ;
struct TYPE_14__ {size_t stream_index; int* frame; size_t eof_count; } ;
typedef  TYPE_1__ MvContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVIndexEntry ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ av_get_packet (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_seek (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_5__*,scalar_t__) ; 
 scalar_t__ avio_tell (TYPE_5__*) ; 

__attribute__((used)) static int mv_read_packet(AVFormatContext *avctx, AVPacket *pkt)
{
    MvContext *mv = avctx->priv_data;
    AVIOContext *pb = avctx->pb;
    AVStream *st = avctx->streams[mv->stream_index];
    const AVIndexEntry *index;
    int frame = mv->frame[mv->stream_index];
    int64_t ret;
    uint64_t pos;

    if (frame < st->nb_index_entries) {
        index = &st->index_entries[frame];
        pos   = avio_tell(pb);
        if (index->pos > pos)
            avio_skip(pb, index->pos - pos);
        else if (index->pos < pos) {
            if (!(pb->seekable & AVIO_SEEKABLE_NORMAL))
                return AVERROR(EIO);
            ret = avio_seek(pb, index->pos, SEEK_SET);
            if (ret < 0)
                return ret;
        }
        ret = av_get_packet(pb, pkt, index->size);
        if (ret < 0)
            return ret;

        pkt->stream_index = mv->stream_index;
        pkt->pts          = index->timestamp;
        pkt->flags       |= AV_PKT_FLAG_KEY;

        mv->frame[mv->stream_index]++;
        mv->eof_count = 0;
    } else {
        mv->eof_count++;
        if (mv->eof_count >= avctx->nb_streams)
            return AVERROR_EOF;

        // avoid returning 0 without a packet
        return AVERROR(EAGAIN);
    }

    mv->stream_index++;
    if (mv->stream_index >= avctx->nb_streams)
        mv->stream_index = 0;

    return 0;
}