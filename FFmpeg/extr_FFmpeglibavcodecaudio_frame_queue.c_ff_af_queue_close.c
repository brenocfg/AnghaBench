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
struct TYPE_4__ {int /*<<< orphan*/  frames; scalar_t__ frame_count; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ AudioFrameQueue ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void ff_af_queue_close(AudioFrameQueue *afq)
{
    if(afq->frame_count)
        av_log(afq->avctx, AV_LOG_WARNING, "%d frames left in the queue on closing\n", afq->frame_count);
    av_freep(&afq->frames);
    memset(afq, 0, sizeof(*afq));
}