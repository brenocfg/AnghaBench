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
struct RingQueue {scalar_t__ length; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */

__attribute__((used)) static int RingQueue_IsAllocated(const struct RingQueue *rq)
{
	if (rq == NULL)
		return 0;
	return (rq->queue != NULL) && (rq->length > 0);
}