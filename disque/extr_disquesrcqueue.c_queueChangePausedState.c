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
typedef  int uint32_t ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */
 int QUEUE_FLAG_PAUSED_OUT ; 
 int /*<<< orphan*/  signalQueueAsReady (TYPE_1__*) ; 

void queueChangePausedState(queue *q, int flag, int set) {
    uint32_t orig_flags = q->flags;

    if (set) q->flags |= flag;
    else     q->flags &= ~flag;

    if ((orig_flags & QUEUE_FLAG_PAUSED_OUT) &&
        !(q->flags & QUEUE_FLAG_PAUSED_OUT))
    {
        signalQueueAsReady(q);
    }
}