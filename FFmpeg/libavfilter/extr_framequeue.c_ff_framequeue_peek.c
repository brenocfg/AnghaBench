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
struct TYPE_8__ {int /*<<< orphan*/ * frame; } ;
struct TYPE_7__ {size_t queued; } ;
typedef  TYPE_1__ FFFrameQueue ;
typedef  TYPE_2__ FFFrameBucket ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (int) ; 
 TYPE_2__* bucket (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  check_consistency (TYPE_1__*) ; 

AVFrame *ff_framequeue_peek(FFFrameQueue *fq, size_t idx)
{
    FFFrameBucket *b;

    check_consistency(fq);
    av_assert1(idx < fq->queued);
    b = bucket(fq, idx);
    check_consistency(fq);
    return b->frame;
}