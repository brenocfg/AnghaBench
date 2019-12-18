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
struct task_struct {scalar_t__ latency_record_count; int /*<<< orphan*/  latency_record; } ;

/* Variables and functions */
 int /*<<< orphan*/  latency_lock ; 
 int /*<<< orphan*/  latencytop_enabled ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void clear_all_latency_tracing(struct task_struct *p)
{
	unsigned long flags;

	if (!latencytop_enabled)
		return;

	spin_lock_irqsave(&latency_lock, flags);
	memset(&p->latency_record, 0, sizeof(p->latency_record));
	p->latency_record_count = 0;
	spin_unlock_irqrestore(&latency_lock, flags);
}