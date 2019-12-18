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
struct work_struct {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING ; 
 int /*<<< orphan*/  __queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_data_bits (struct work_struct*) ; 
 int /*<<< orphan*/  wq_per_cpu (struct workqueue_struct*,int) ; 

int
queue_work_on(int cpu, struct workqueue_struct *wq, struct work_struct *work)
{
	int ret = 0;

	if (!test_and_set_bit(WORK_STRUCT_PENDING, work_data_bits(work))) {
		BUG_ON(!list_empty(&work->entry));
		__queue_work(wq_per_cpu(wq, cpu), work);
		ret = 1;
	}
	return ret;
}