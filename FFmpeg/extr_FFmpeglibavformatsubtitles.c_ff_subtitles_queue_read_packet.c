#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  dts; } ;
struct TYPE_7__ {int current_sub_idx; scalar_t__ nb_subs; TYPE_2__* subs; } ;
typedef  TYPE_1__ FFDemuxSubtitlesQueue ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_packet_ref (TYPE_2__*,TYPE_2__*) ; 

int ff_subtitles_queue_read_packet(FFDemuxSubtitlesQueue *q, AVPacket *pkt)
{
    AVPacket *sub = q->subs + q->current_sub_idx;

    if (q->current_sub_idx == q->nb_subs)
        return AVERROR_EOF;
    if (av_packet_ref(pkt, sub) < 0) {
        return AVERROR(ENOMEM);
    }

    pkt->dts = pkt->pts;
    q->current_sub_idx++;
    return 0;
}