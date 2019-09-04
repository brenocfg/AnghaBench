#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FFFrameQueue ;

/* Variables and functions */

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