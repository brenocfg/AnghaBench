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
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ stream_index; scalar_t__ dts; int flags; scalar_t__ data; } ;
struct playlist {scalar_t__ seek_timestamp; scalar_t__ seek_stream_index; int seek_flags; scalar_t__ n_main_streams; TYPE_5__ pkt; TYPE_3__** main_streams; TYPE_17__* ctx; scalar_t__ has_noheader_flag; scalar_t__ is_id3_timestamped; int /*<<< orphan*/  pb; scalar_t__ needed; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_27__ {TYPE_2__* priv_data; } ;
struct TYPE_25__ {int /*<<< orphan*/  den; } ;
struct TYPE_24__ {size_t index; TYPE_1__* codecpar; TYPE_4__ time_base; int /*<<< orphan*/  event_flags; int /*<<< orphan*/  metadata; } ;
struct TYPE_23__ {int n_playlists; scalar_t__ first_timestamp; void* cur_timestamp; struct playlist** playlists; scalar_t__ first_packet; } ;
struct TYPE_22__ {scalar_t__ codec_id; } ;
struct TYPE_21__ {int event_flags; int ctx_flags; TYPE_3__** streams; int /*<<< orphan*/  nb_streams; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ HLSContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVRational ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int AVERROR_EOF ; 
 int AVFMTCTX_NOHEADER ; 
 int AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int AVSEEK_FLAG_ANY ; 
 int /*<<< orphan*/  AVSTREAM_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_ROUND_DOWN ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int av_read_frame (TYPE_17__*,TYPE_5__*) ; 
 void* av_rescale_q (scalar_t__,TYPE_4__,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_rnd (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 scalar_t__ compare_ts_with_wrapdetect (scalar_t__,struct playlist*,scalar_t__,struct playlist*) ; 
 int /*<<< orphan*/  fill_timing_for_id3_timestamped_stream (struct playlist*) ; 
 TYPE_4__ get_timebase (struct playlist*) ; 
 int /*<<< orphan*/  recheck_discard_flags (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  reset_packet (TYPE_5__*) ; 
 int set_stream_info_from_input_stream (TYPE_3__*,struct playlist*,TYPE_3__*) ; 
 int /*<<< orphan*/  update_noheader_flag (TYPE_6__*) ; 
 int update_streams_from_subdemuxer (TYPE_6__*,struct playlist*) ; 

__attribute__((used)) static int hls_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    HLSContext *c = s->priv_data;
    int ret, i, minplaylist = -1;

    recheck_discard_flags(s, c->first_packet);
    c->first_packet = 0;

    for (i = 0; i < c->n_playlists; i++) {
        struct playlist *pls = c->playlists[i];
        /* Make sure we've got one buffered packet from each open playlist
         * stream */
        if (pls->needed && !pls->pkt.data) {
            while (1) {
                int64_t ts_diff;
                AVRational tb;
                ret = av_read_frame(pls->ctx, &pls->pkt);
                if (ret < 0) {
                    if (!avio_feof(&pls->pb) && ret != AVERROR_EOF)
                        return ret;
                    reset_packet(&pls->pkt);
                    break;
                } else {
                    /* stream_index check prevents matching picture attachments etc. */
                    if (pls->is_id3_timestamped && pls->pkt.stream_index == 0) {
                        /* audio elementary streams are id3 timestamped */
                        fill_timing_for_id3_timestamped_stream(pls);
                    }

                    if (c->first_timestamp == AV_NOPTS_VALUE &&
                        pls->pkt.dts       != AV_NOPTS_VALUE)
                        c->first_timestamp = av_rescale_q(pls->pkt.dts,
                            get_timebase(pls), AV_TIME_BASE_Q);
                }

                if (pls->seek_timestamp == AV_NOPTS_VALUE)
                    break;

                if (pls->seek_stream_index < 0 ||
                    pls->seek_stream_index == pls->pkt.stream_index) {

                    if (pls->pkt.dts == AV_NOPTS_VALUE) {
                        pls->seek_timestamp = AV_NOPTS_VALUE;
                        break;
                    }

                    tb = get_timebase(pls);
                    ts_diff = av_rescale_rnd(pls->pkt.dts, AV_TIME_BASE,
                                            tb.den, AV_ROUND_DOWN) -
                            pls->seek_timestamp;
                    if (ts_diff >= 0 && (pls->seek_flags  & AVSEEK_FLAG_ANY ||
                                        pls->pkt.flags & AV_PKT_FLAG_KEY)) {
                        pls->seek_timestamp = AV_NOPTS_VALUE;
                        break;
                    }
                }
                av_packet_unref(&pls->pkt);
            }
        }
        /* Check if this stream has the packet with the lowest dts */
        if (pls->pkt.data) {
            struct playlist *minpls = minplaylist < 0 ?
                                     NULL : c->playlists[minplaylist];
            if (minplaylist < 0) {
                minplaylist = i;
            } else {
                int64_t dts     =    pls->pkt.dts;
                int64_t mindts  = minpls->pkt.dts;

                if (dts == AV_NOPTS_VALUE ||
                    (mindts != AV_NOPTS_VALUE && compare_ts_with_wrapdetect(dts, pls, mindts, minpls) < 0))
                    minplaylist = i;
            }
        }
    }

    /* If we got a packet, return it */
    if (minplaylist >= 0) {
        struct playlist *pls = c->playlists[minplaylist];
        AVStream *ist;
        AVStream *st;

        ret = update_streams_from_subdemuxer(s, pls);
        if (ret < 0) {
            av_packet_unref(&pls->pkt);
            return ret;
        }

        // If sub-demuxer reports updated metadata, copy it to the first stream
        // and set its AVSTREAM_EVENT_FLAG_METADATA_UPDATED flag.
        if (pls->ctx->event_flags & AVFMT_EVENT_FLAG_METADATA_UPDATED) {
            if (pls->n_main_streams) {
                st = pls->main_streams[0];
                av_dict_copy(&st->metadata, pls->ctx->metadata, 0);
                st->event_flags |= AVSTREAM_EVENT_FLAG_METADATA_UPDATED;
            }
            pls->ctx->event_flags &= ~AVFMT_EVENT_FLAG_METADATA_UPDATED;
        }

        /* check if noheader flag has been cleared by the subdemuxer */
        if (pls->has_noheader_flag && !(pls->ctx->ctx_flags & AVFMTCTX_NOHEADER)) {
            pls->has_noheader_flag = 0;
            update_noheader_flag(s);
        }

        if (pls->pkt.stream_index >= pls->n_main_streams) {
            av_log(s, AV_LOG_ERROR, "stream index inconsistency: index %d, %d main streams, %d subdemuxer streams\n",
                   pls->pkt.stream_index, pls->n_main_streams, pls->ctx->nb_streams);
            av_packet_unref(&pls->pkt);
            return AVERROR_BUG;
        }

        ist = pls->ctx->streams[pls->pkt.stream_index];
        st = pls->main_streams[pls->pkt.stream_index];

        *pkt = pls->pkt;
        pkt->stream_index = st->index;
        reset_packet(&c->playlists[minplaylist]->pkt);

        if (pkt->dts != AV_NOPTS_VALUE)
            c->cur_timestamp = av_rescale_q(pkt->dts,
                                            ist->time_base,
                                            AV_TIME_BASE_Q);

        /* There may be more situations where this would be useful, but this at least
         * handles newly probed codecs properly (i.e. request_probe by mpegts). */
        if (ist->codecpar->codec_id != st->codecpar->codec_id) {
            ret = set_stream_info_from_input_stream(st, pls, ist);
            if (ret < 0) {
                av_packet_unref(pkt);
                return ret;
            }
        }

        return 0;
    }
    return AVERROR_EOF;
}