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
struct work_struct {int /*<<< orphan*/  data; } ;
struct cpu_workqueue_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long WORK_STRUCT_FLAG_MASK ; 
 unsigned long WORK_STRUCT_PENDING ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long* work_data_bits (struct work_struct*) ; 
 int /*<<< orphan*/  work_pending (struct work_struct*) ; 

__attribute__((used)) static inline void set_wq_data(struct work_struct *work,
				struct cpu_workqueue_struct *cwq)
{
	unsigned long new;

	BUG_ON(!work_pending(work));

	new = (unsigned long) cwq | (1UL << WORK_STRUCT_PENDING);
	new |= WORK_STRUCT_FLAG_MASK & *work_data_bits(work);
	atomic_long_set(&work->data, new);
}