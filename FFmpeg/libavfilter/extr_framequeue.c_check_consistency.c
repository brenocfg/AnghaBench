#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {TYPE_1__* frame; } ;
struct TYPE_7__ {size_t queued; size_t total_frames_head; size_t total_frames_tail; scalar_t__ total_samples_head; scalar_t__ total_samples_tail; } ;
struct TYPE_6__ {scalar_t__ nb_samples; } ;
typedef  TYPE_2__ FFFrameQueue ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_4__* bucket (TYPE_2__*,size_t) ; 

__attribute__((used)) static void check_consistency(FFFrameQueue *fq)
{
#if defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    uint64_t nb_samples = 0;
    size_t i;

    av_assert0(fq->queued == fq->total_frames_head - fq->total_frames_tail);
    for (i = 0; i < fq->queued; i++)
        nb_samples += bucket(fq, i)->frame->nb_samples;
    av_assert0(nb_samples == fq->total_samples_head - fq->total_samples_tail);
#endif
}