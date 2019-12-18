#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_6__ {scalar_t__ pts; scalar_t__ duration; } ;
struct TYPE_5__ {int frame_count; scalar_t__ remaining_samples; scalar_t__ remaining_delay; int /*<<< orphan*/  avctx; TYPE_2__* frames; scalar_t__ frame_alloc; } ;
typedef  TYPE_1__ AudioFrameQueue ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int FFMIN (scalar_t__,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int ff_samples_to_time_base (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 

void ff_af_queue_remove(AudioFrameQueue *afq, int nb_samples, int64_t *pts,
                        int64_t *duration)
{
    int64_t out_pts = AV_NOPTS_VALUE;
    int removed_samples = 0;
    int i;

    if (afq->frame_count || afq->frame_alloc) {
        if (afq->frames->pts != AV_NOPTS_VALUE)
            out_pts = afq->frames->pts;
    }
    if(!afq->frame_count)
        av_log(afq->avctx, AV_LOG_WARNING, "Trying to remove %d samples, but the queue is empty\n", nb_samples);
    if (pts)
        *pts = ff_samples_to_time_base(afq->avctx, out_pts);

    for(i=0; nb_samples && i<afq->frame_count; i++){
        int n= FFMIN(afq->frames[i].duration, nb_samples);
        afq->frames[i].duration -= n;
        nb_samples              -= n;
        removed_samples         += n;
        if(afq->frames[i].pts != AV_NOPTS_VALUE)
            afq->frames[i].pts      += n;
    }
    afq->remaining_samples -= removed_samples;
    i -= i && afq->frames[i-1].duration;
    memmove(afq->frames, afq->frames + i, sizeof(*afq->frames) * (afq->frame_count - i));
    afq->frame_count -= i;

    if(nb_samples){
        av_assert0(!afq->frame_count);
        av_assert0(afq->remaining_samples == afq->remaining_delay);
        if(afq->frames && afq->frames[0].pts != AV_NOPTS_VALUE)
            afq->frames[0].pts += nb_samples;
        av_log(afq->avctx, AV_LOG_DEBUG, "Trying to remove %d more samples than there are in the queue\n", nb_samples);
    }
    if (duration)
        *duration = ff_samples_to_time_base(afq->avctx, removed_samples);
}