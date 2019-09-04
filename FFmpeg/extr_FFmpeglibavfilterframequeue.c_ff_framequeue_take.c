#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ nb_samples; } ;
struct TYPE_10__ {TYPE_3__* frame; } ;
struct TYPE_9__ {int tail; int allocated; scalar_t__ samples_skipped; int /*<<< orphan*/  total_samples_tail; int /*<<< orphan*/  total_frames_tail; int /*<<< orphan*/  queued; } ;
typedef  TYPE_1__ FFFrameQueue ;
typedef  TYPE_2__ FFFrameBucket ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* bucket (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_consistency (TYPE_1__*) ; 

AVFrame *ff_framequeue_take(FFFrameQueue *fq)
{
    FFFrameBucket *b;

    check_consistency(fq);
    av_assert1(fq->queued);
    b = bucket(fq, 0);
    fq->queued--;
    fq->tail++;
    fq->tail &= fq->allocated - 1;
    fq->total_frames_tail++;
    fq->total_samples_tail += b->frame->nb_samples;
    fq->samples_skipped = 0;
    check_consistency(fq);
    return b->frame;
}