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
struct wq_barrier {int /*<<< orphan*/  work; int /*<<< orphan*/  done; } ;
struct list_head {int dummy; } ;
struct cpu_workqueue_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_work (struct cpu_workqueue_struct*,int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  work_data_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_barrier_func ; 

__attribute__((used)) static void insert_wq_barrier(struct cpu_workqueue_struct *cwq,
			struct wq_barrier *barr, struct list_head *head)
{
	INIT_WORK(&barr->work, wq_barrier_func);
	__set_bit(WORK_STRUCT_PENDING, work_data_bits(&barr->work));

	init_completion(&barr->done);

	insert_work(cwq, &barr->work, head);
}