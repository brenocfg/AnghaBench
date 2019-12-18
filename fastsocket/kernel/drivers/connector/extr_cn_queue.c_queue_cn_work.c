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
struct work_struct {int dummy; } ;
struct cn_queue_dev {int /*<<< orphan*/  wq_requested; struct work_struct wq_creation; int /*<<< orphan*/  cn_queue; } ;
struct cn_callback_entry {struct cn_queue_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int schedule_work (struct work_struct*) ; 

int queue_cn_work(struct cn_callback_entry *cbq, struct work_struct *work)
{
	struct cn_queue_dev *pdev = cbq->pdev;

	if (likely(pdev->cn_queue))
		return queue_work(pdev->cn_queue, work);

	/* Don't create the connector workqueue twice */
	if (atomic_inc_return(&pdev->wq_requested) == 1)
		schedule_work(&pdev->wq_creation);
	else
		atomic_dec(&pdev->wq_requested);

	return schedule_work(work);
}