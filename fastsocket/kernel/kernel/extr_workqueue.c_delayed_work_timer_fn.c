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
struct workqueue_struct {int dummy; } ;
struct delayed_work {int /*<<< orphan*/  work; } ;
struct cpu_workqueue_struct {struct workqueue_struct* wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cpu_workqueue_struct* get_wq_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  wq_per_cpu (struct workqueue_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delayed_work_timer_fn(unsigned long __data)
{
	struct delayed_work *dwork = (struct delayed_work *)__data;
	struct cpu_workqueue_struct *cwq = get_wq_data(&dwork->work);
	struct workqueue_struct *wq = cwq->wq;

	__queue_work(wq_per_cpu(wq, smp_processor_id()), &dwork->work);
}