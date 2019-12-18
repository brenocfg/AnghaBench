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
struct cfq_queue {int dummy; } ;
struct cfq_data {struct cfq_queue* async_idle_cfqq; struct cfq_queue*** async_cfqq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  IOPRIO_CLASS_BE 130 
#define  IOPRIO_CLASS_IDLE 129 
#define  IOPRIO_CLASS_RT 128 

__attribute__((used)) static struct cfq_queue **
cfq_async_queue_prio(struct cfq_data *cfqd, int ioprio_class, int ioprio)
{
	switch (ioprio_class) {
	case IOPRIO_CLASS_RT:
		return &cfqd->async_cfqq[0][ioprio];
	case IOPRIO_CLASS_BE:
		return &cfqd->async_cfqq[1][ioprio];
	case IOPRIO_CLASS_IDLE:
		return &cfqd->async_idle_cfqq;
	default:
		BUG();
	}
}