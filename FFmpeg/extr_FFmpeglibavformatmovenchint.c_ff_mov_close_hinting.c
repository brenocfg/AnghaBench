#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pb; } ;
struct TYPE_6__ {int /*<<< orphan*/  sample_queue; int /*<<< orphan*/  par; TYPE_2__* rtp_ctx; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_write_trailer (TYPE_2__*) ; 
 int /*<<< orphan*/  avcodec_parameters_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_2__*) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (scalar_t__*) ; 
 int /*<<< orphan*/  sample_queue_free (int /*<<< orphan*/ *) ; 

void ff_mov_close_hinting(MOVTrack *track)
{
    AVFormatContext *rtp_ctx = track->rtp_ctx;

    avcodec_parameters_free(&track->par);
    sample_queue_free(&track->sample_queue);
    if (!rtp_ctx)
        return;
    if (rtp_ctx->pb) {
        av_write_trailer(rtp_ctx);
        ffio_free_dyn_buf(&rtp_ctx->pb);
    }
    avformat_free_context(rtp_ctx);
}