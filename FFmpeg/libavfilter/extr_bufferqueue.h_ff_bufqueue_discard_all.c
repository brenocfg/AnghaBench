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
struct FFBufQueue {scalar_t__ available; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * ff_bufqueue_get (struct FFBufQueue*) ; 

__attribute__((used)) static inline void ff_bufqueue_discard_all(struct FFBufQueue *queue)
{
    while (queue->available) {
        AVFrame *buf = ff_bufqueue_get(queue);
        av_frame_free(&buf);
    }
}