#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/  first_bucket; scalar_t__ queued; } ;
typedef  TYPE_1__ FFFrameQueue ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ff_framequeue_take (TYPE_1__*) ; 

void ff_framequeue_free(FFFrameQueue *fq)
{
    while (fq->queued) {
        AVFrame *frame = ff_framequeue_take(fq);
        av_frame_free(&frame);
    }
    if (fq->queue != &fq->first_bucket)
        av_freep(&fq->queue);
}