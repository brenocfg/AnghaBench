#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_type; } ;
struct TYPE_17__ {TYPE_2__** streams; } ;
struct TYPE_16__ {int /*<<< orphan*/ ** streams; TYPE_4__* priv_data; } ;
struct TYPE_15__ {TYPE_3__* tracks; } ;
struct TYPE_14__ {int src_track; int timescale; int hint_track; TYPE_9__* par; TYPE_6__* rtp_ctx; int /*<<< orphan*/  tag; } ;
struct TYPE_12__ {int den; } ;
struct TYPE_13__ {TYPE_1__ time_base; } ;
typedef  TYPE_3__ MOVTrack ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  RTP_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_9__* avcodec_parameters_alloc () ; 
 int /*<<< orphan*/  avcodec_parameters_free (TYPE_9__**) ; 
 int ff_rtp_chain_mux_open (TYPE_6__**,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ff_mov_init_hinting(AVFormatContext *s, int index, int src_index)
{
    MOVMuxContext *mov  = s->priv_data;
    MOVTrack *track     = &mov->tracks[index];
    MOVTrack *src_track = &mov->tracks[src_index];
    AVStream *src_st    = s->streams[src_index];
    int ret = AVERROR(ENOMEM);

    track->tag = MKTAG('r','t','p',' ');
    track->src_track = src_index;

    track->par = avcodec_parameters_alloc();
    if (!track->par)
        goto fail;
    track->par->codec_type = AVMEDIA_TYPE_DATA;
    track->par->codec_tag  = track->tag;

    ret = ff_rtp_chain_mux_open(&track->rtp_ctx, s, src_st, NULL,
                                RTP_MAX_PACKET_SIZE, src_index);
    if (ret < 0)
        goto fail;

    /* Copy the RTP AVStream timebase back to the hint AVStream */
    track->timescale = track->rtp_ctx->streams[0]->time_base.den;

    /* Mark the hinted track that packets written to it should be
     * sent to this track for hinting. */
    src_track->hint_track = index;
    return 0;
fail:
    av_log(s, AV_LOG_WARNING,
           "Unable to initialize hinting of stream %d\n", src_index);
    avcodec_parameters_free(&track->par);
    /* Set a default timescale, to avoid crashes in av_dump_format */
    track->timescale = 90000;
    return ret;
}