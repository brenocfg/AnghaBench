#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; scalar_t__ own_data; } ;
struct TYPE_5__ {int len; TYPE_3__* samples; } ;
typedef  TYPE_1__ HintSampleQueue ;
typedef  int /*<<< orphan*/  HintSample ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static void sample_queue_pop(HintSampleQueue *queue)
{
    if (queue->len <= 0)
        return;
    if (queue->samples[0].own_data)
        av_freep(&queue->samples[0].data);
    queue->len--;
    memmove(queue->samples, queue->samples + 1, sizeof(HintSample)*queue->len);
}