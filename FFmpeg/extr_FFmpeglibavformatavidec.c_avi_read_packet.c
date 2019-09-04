#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_32__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; TYPE_6__* priv_data; } ;
struct TYPE_31__ {int non_interleaved; size_t stream_index; int index_loaded; int dts_max; scalar_t__ dv_demux; int /*<<< orphan*/  last_pkt_pos; } ;
struct TYPE_30__ {int sample_size; int remaining; scalar_t__ frame_offset; scalar_t__ seek_pos; scalar_t__ packet_size; scalar_t__ has_pal; int /*<<< orphan*/  pal; } ;
struct TYPE_29__ {scalar_t__ timestamp; int flags; } ;
struct TYPE_28__ {unsigned int size; int* data; scalar_t__ pos; scalar_t__ dts; int stream_index; int /*<<< orphan*/  flags; int /*<<< orphan*/ * buf; } ;
struct TYPE_27__ {int nb_index_entries; int /*<<< orphan*/  time_base; TYPE_1__* codecpar; TYPE_4__* index_entries; TYPE_5__* priv_data; } ;
struct TYPE_26__ {scalar_t__ codec_type; scalar_t__ codec_id; int /*<<< orphan*/  codec_tag; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVIndexEntry ;
typedef  TYPE_5__ AVIStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVIContext ;
typedef  TYPE_7__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVINDEX_KEYFRAME ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AVSEEK_FLAG_ANY ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ CONFIG_DV_DEMUXER ; 
 int FFMIN (int,int) ; 
 int INT_MAX ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int av_index_search_timestamp (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int* av_packet_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avi_sync (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int avpriv_dv_get_packet (scalar_t__,TYPE_3__*) ; 
 int avpriv_dv_produce_packet (scalar_t__,TYPE_3__*,int*,unsigned int,scalar_t__) ; 
 int* avpriv_find_start_code (int const*,int const*,int*) ; 
 scalar_t__ get_duration (TYPE_5__*,unsigned int) ; 
 scalar_t__ get_subtitle_pkt (TYPE_7__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ni_prepare_read (TYPE_7__*) ; 
 scalar_t__ read_gab2_sub (TYPE_7__*,TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int avi_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIContext *avi = s->priv_data;
    AVIOContext *pb = s->pb;
    int err;

    if (CONFIG_DV_DEMUXER && avi->dv_demux) {
        int size = avpriv_dv_get_packet(avi->dv_demux, pkt);
        if (size >= 0)
            return size;
        else
            goto resync;
    }

    if (avi->non_interleaved) {
        err = ni_prepare_read(s);
        if (err < 0)
            return err;
    }

resync:
    if (avi->stream_index >= 0) {
        AVStream *st   = s->streams[avi->stream_index];
        AVIStream *ast = st->priv_data;
        int size, err;

        if (get_subtitle_pkt(s, st, pkt))
            return 0;

        // minorityreport.AVI block_align=1024 sample_size=1 IMA-ADPCM
        if (ast->sample_size <= 1)
            size = INT_MAX;
        else if (ast->sample_size < 32)
            // arbitrary multiplier to avoid tiny packets for raw PCM data
            size = 1024 * ast->sample_size;
        else
            size = ast->sample_size;

        if (size > ast->remaining)
            size = ast->remaining;
        avi->last_pkt_pos = avio_tell(pb);
        err               = av_get_packet(pb, pkt, size);
        if (err < 0)
            return err;
        size = err;

        if (ast->has_pal && pkt->size < (unsigned)INT_MAX / 2) {
            uint8_t *pal;
            pal = av_packet_new_side_data(pkt,
                                          AV_PKT_DATA_PALETTE,
                                          AVPALETTE_SIZE);
            if (!pal) {
                av_log(s, AV_LOG_ERROR,
                       "Failed to allocate data for palette\n");
            } else {
                memcpy(pal, ast->pal, AVPALETTE_SIZE);
                ast->has_pal = 0;
            }
        }

        if (CONFIG_DV_DEMUXER && avi->dv_demux) {
            AVBufferRef *avbuf = pkt->buf;
            size = avpriv_dv_produce_packet(avi->dv_demux, pkt,
                                            pkt->data, pkt->size, pkt->pos);
            pkt->buf    = avbuf;
            pkt->flags |= AV_PKT_FLAG_KEY;
            if (size < 0)
                av_packet_unref(pkt);
        } else if (st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE &&
                   !st->codecpar->codec_tag && read_gab2_sub(s, st, pkt)) {
            ast->frame_offset++;
            avi->stream_index = -1;
            ast->remaining    = 0;
            goto resync;
        } else {
            /* XXX: How to handle B-frames in AVI? */
            pkt->dts = ast->frame_offset;
//                pkt->dts += ast->start;
            if (ast->sample_size)
                pkt->dts /= ast->sample_size;
            pkt->stream_index = avi->stream_index;

            if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && st->index_entries) {
                AVIndexEntry *e;
                int index;

                index = av_index_search_timestamp(st, ast->frame_offset, AVSEEK_FLAG_ANY);
                e     = &st->index_entries[index];

                if (index >= 0 && e->timestamp == ast->frame_offset) {
                    if (index == st->nb_index_entries-1) {
                        int key=1;
                        uint32_t state=-1;
                        if (st->codecpar->codec_id == AV_CODEC_ID_MPEG4) {
                            const uint8_t *ptr = pkt->data, *end = ptr + FFMIN(size, 256);
                            while (ptr < end) {
                                ptr = avpriv_find_start_code(ptr, end, &state);
                                if (state == 0x1B6 && ptr < end) {
                                    key = !(*ptr & 0xC0);
                                    break;
                                }
                            }
                        }
                        if (!key)
                            e->flags &= ~AVINDEX_KEYFRAME;
                    }
                    if (e->flags & AVINDEX_KEYFRAME)
                        pkt->flags |= AV_PKT_FLAG_KEY;
                }
            } else {
                pkt->flags |= AV_PKT_FLAG_KEY;
            }
            ast->frame_offset += get_duration(ast, pkt->size);
        }
        ast->remaining -= err;
        if (!ast->remaining) {
            avi->stream_index = -1;
            ast->packet_size  = 0;
        }

        if (!avi->non_interleaved && pkt->pos >= 0 && ast->seek_pos > pkt->pos) {
            av_packet_unref(pkt);
            goto resync;
        }
        ast->seek_pos= 0;

        if (!avi->non_interleaved && st->nb_index_entries>1 && avi->index_loaded>1) {
            int64_t dts= av_rescale_q(pkt->dts, st->time_base, AV_TIME_BASE_Q);

            if (avi->dts_max - dts > 2*AV_TIME_BASE) {
                avi->non_interleaved= 1;
                av_log(s, AV_LOG_INFO, "Switching to NI mode, due to poor interleaving\n");
            }else if (avi->dts_max < dts)
                avi->dts_max = dts;
        }

        return 0;
    }

    if ((err = avi_sync(s, 0)) < 0)
        return err;
    goto resync;
}