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
struct delayed_work {int /*<<< orphan*/  work; int /*<<< orphan*/  timer; } ;
struct cpu_workqueue_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __queue_work (struct cpu_workqueue_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  keventd_wq ; 
 int /*<<< orphan*/  put_cpu () ; 
 struct cpu_workqueue_struct* wq_per_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void flush_delayed_work(struct delayed_work *dwork)
{
	if (del_timer_sync(&dwork->timer)) {
		struct cpu_workqueue_struct *cwq;
		cwq = wq_per_cpu(keventd_wq, get_cpu());
		__queue_work(cwq, &dwork->work);
		put_cpu();
	}
	flush_work(&dwork->work);
}