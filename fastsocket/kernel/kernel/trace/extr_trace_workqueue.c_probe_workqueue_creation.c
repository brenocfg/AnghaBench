#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  pid; } ;
struct cpu_workqueue_stats {int cpu; int /*<<< orphan*/  list; int /*<<< orphan*/  pid; int /*<<< orphan*/  kref; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cpu_workqueue_stats* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* workqueue_cpu_stat (int) ; 

__attribute__((used)) static void probe_workqueue_creation(struct task_struct *wq_thread, int cpu)
{
	struct cpu_workqueue_stats *cws;
	unsigned long flags;

	WARN_ON(cpu < 0);

	/* Workqueues are sometimes created in atomic context */
	cws = kzalloc(sizeof(struct cpu_workqueue_stats), GFP_ATOMIC);
	if (!cws) {
		pr_warning("trace_workqueue: not enough memory\n");
		return;
	}
	INIT_LIST_HEAD(&cws->list);
	kref_init(&cws->kref);
	cws->cpu = cpu;
	cws->pid = wq_thread->pid;

	spin_lock_irqsave(&workqueue_cpu_stat(cpu)->lock, flags);
	list_add_tail(&cws->list, &workqueue_cpu_stat(cpu)->list);
	spin_unlock_irqrestore(&workqueue_cpu_stat(cpu)->lock, flags);
}