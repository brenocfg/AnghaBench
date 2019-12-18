#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int audio_stream_index; int video_stream_index; scalar_t__ audio_frame_count; scalar_t__ video_pts; scalar_t__ audio_channels; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  frame_rate; } ;
typedef  TYPE_1__ RoqDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AV_RL16 (unsigned char*) ; 
 int /*<<< orphan*/  EIO ; 
 int RoQ_CHUNK_PREAMBLE_SIZE ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int roq_read_header(AVFormatContext *s)
{
    RoqDemuxContext *roq = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned char preamble[RoQ_CHUNK_PREAMBLE_SIZE];

    /* get the main header */
    if (avio_read(pb, preamble, RoQ_CHUNK_PREAMBLE_SIZE) !=
        RoQ_CHUNK_PREAMBLE_SIZE)
        return AVERROR(EIO);
    roq->frame_rate = AV_RL16(&preamble[6]);

    /* init private context parameters */
    roq->width = roq->height = roq->audio_channels = roq->video_pts =
    roq->audio_frame_count = 0;
    roq->audio_stream_index = -1;
    roq->video_stream_index = -1;

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    return 0;
}