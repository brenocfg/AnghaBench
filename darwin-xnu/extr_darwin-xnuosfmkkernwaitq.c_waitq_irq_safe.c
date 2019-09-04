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
struct waitq {int waitq_irq; } ;

/* Variables and functions */

int waitq_irq_safe(struct waitq *waitq)
{
	/* global wait queues have this bit set on initialization */
	return waitq->waitq_irq;
}