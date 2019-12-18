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
struct apm_queue {scalar_t__ event_head; scalar_t__ event_tail; } ;

/* Variables and functions */

__attribute__((used)) static inline int queue_empty(struct apm_queue *q)
{
	return q->event_head == q->event_tail;
}