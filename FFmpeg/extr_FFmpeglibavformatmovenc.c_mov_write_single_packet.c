#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_22__ {scalar_t__ codec_id; int extradata_size; scalar_t__ codec_type; void* extradata; } ;
struct TYPE_21__ {int nb_streams; TYPE_2__** streams; TYPE_4__* priv_data; } ;
struct TYPE_20__ {size_t stream_index; int size; scalar_t__ pts; scalar_t__ dts; int flags; } ;
struct TYPE_19__ {int flags; int need_rewrite_extradata; scalar_t__ max_fragment_duration; scalar_t__ max_fragment_size; scalar_t__ mdat_size; scalar_t__ min_fragment_duration; TYPE_3__* tracks; } ;
struct TYPE_18__ {int frag_discont; scalar_t__ dts_shift; scalar_t__ start_dts; scalar_t__ start_cts; scalar_t__ track_duration; scalar_t__ end_pts; int end_reliable; scalar_t__ entry; TYPE_1__* cluster; TYPE_7__* par; } ;
struct TYPE_17__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_16__ {scalar_t__ dts; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_AAC ; 
 scalar_t__ AV_CODEC_ID_AV1 ; 
 scalar_t__ AV_CODEC_ID_FLAC ; 
 scalar_t__ AV_CODEC_ID_MP4ALS ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_MOV_FLAG_FRAG_DISCONT ; 
 int FF_MOV_FLAG_FRAG_EVERY_FRAME ; 
 int FF_MOV_FLAG_FRAG_KEYFRAME ; 
 int FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS ; 
 int /*<<< orphan*/  av_free (void*) ; 
 void* av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_5__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_pkt (TYPE_6__*,TYPE_5__*) ; 
 int ff_mov_write_packet (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mov_auto_flush_fragment (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_single_packet(AVFormatContext *s, AVPacket *pkt)
{
        MOVMuxContext *mov = s->priv_data;
        MOVTrack *trk = &mov->tracks[pkt->stream_index];
        AVCodecParameters *par = trk->par;
        int64_t frag_duration = 0;
        int size = pkt->size;

        int ret = check_pkt(s, pkt);
        if (ret < 0)
            return ret;

        if (mov->flags & FF_MOV_FLAG_FRAG_DISCONT) {
            int i;
            for (i = 0; i < s->nb_streams; i++)
                mov->tracks[i].frag_discont = 1;
            mov->flags &= ~FF_MOV_FLAG_FRAG_DISCONT;
        }

        if (mov->flags & FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS) {
            if (trk->dts_shift == AV_NOPTS_VALUE)
                trk->dts_shift = pkt->pts - pkt->dts;
            pkt->dts += trk->dts_shift;
        }

        if (trk->par->codec_id == AV_CODEC_ID_MP4ALS ||
            trk->par->codec_id == AV_CODEC_ID_AAC ||
            trk->par->codec_id == AV_CODEC_ID_AV1 ||
            trk->par->codec_id == AV_CODEC_ID_FLAC) {
            int side_size = 0;
            uint8_t *side = av_packet_get_side_data(pkt, AV_PKT_DATA_NEW_EXTRADATA, &side_size);
            if (side && side_size > 0 && (side_size != par->extradata_size || memcmp(side, par->extradata, side_size))) {
                void *newextra = av_mallocz(side_size + AV_INPUT_BUFFER_PADDING_SIZE);
                if (!newextra)
                    return AVERROR(ENOMEM);
                av_free(par->extradata);
                par->extradata = newextra;
                memcpy(par->extradata, side, side_size);
                par->extradata_size = side_size;
                if (!pkt->size) // Flush packet
                    mov->need_rewrite_extradata = 1;
            }
        }

        if (!pkt->size) {
            if (trk->start_dts == AV_NOPTS_VALUE && trk->frag_discont) {
                trk->start_dts = pkt->dts;
                if (pkt->pts != AV_NOPTS_VALUE)
                    trk->start_cts = pkt->pts - pkt->dts;
                else
                    trk->start_cts = 0;
            }

            return 0;             /* Discard 0 sized packets */
        }

        if (trk->entry && pkt->stream_index < s->nb_streams)
            frag_duration = av_rescale_q(pkt->dts - trk->cluster[0].dts,
                                         s->streams[pkt->stream_index]->time_base,
                                         AV_TIME_BASE_Q);
        if ((mov->max_fragment_duration &&
             frag_duration >= mov->max_fragment_duration) ||
             (mov->max_fragment_size && mov->mdat_size + size >= mov->max_fragment_size) ||
             (mov->flags & FF_MOV_FLAG_FRAG_KEYFRAME &&
              par->codec_type == AVMEDIA_TYPE_VIDEO &&
              trk->entry && pkt->flags & AV_PKT_FLAG_KEY) ||
              (mov->flags & FF_MOV_FLAG_FRAG_EVERY_FRAME)) {
            if (frag_duration >= mov->min_fragment_duration) {
                // Set the duration of this track to line up with the next
                // sample in this track. This avoids relying on AVPacket
                // duration, but only helps for this particular track, not
                // for the other ones that are flushed at the same time.
                trk->track_duration = pkt->dts - trk->start_dts;
                if (pkt->pts != AV_NOPTS_VALUE)
                    trk->end_pts = pkt->pts;
                else
                    trk->end_pts = pkt->dts;
                trk->end_reliable = 1;
                mov_auto_flush_fragment(s, 0);
            }
        }

        return ff_mov_write_packet(s, pkt);
}