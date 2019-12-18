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
struct FFBufQueue {size_t head; int /*<<< orphan*/ ** queue; int /*<<< orphan*/  available; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int FF_BUFQUEUE_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline AVFrame *ff_bufqueue_get(struct FFBufQueue *queue)
{
    AVFrame *ret = queue->queue[queue->head];
    av_assert0(queue->available);
    queue->available--;
    queue->queue[queue->head] = NULL;
    queue->head = (queue->head + 1) % FF_BUFQUEUE_SIZE;
    return ret;
}