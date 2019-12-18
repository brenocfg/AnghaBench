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
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  slow_work_queue_lock ; 
 void* slow_work_runqueue_index (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *slow_work_runqueue_start(struct seq_file *m, loff_t *_pos)
{
	spin_lock_irq(&slow_work_queue_lock);
	return slow_work_runqueue_index(m, _pos);
}