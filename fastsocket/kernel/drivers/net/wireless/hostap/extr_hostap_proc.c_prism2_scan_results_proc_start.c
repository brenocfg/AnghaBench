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
struct seq_file {TYPE_1__* private; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ last_scan_results_count; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *prism2_scan_results_proc_start(struct seq_file *m, loff_t *_pos)
{
	local_info_t *local = m->private;
	spin_lock_bh(&local->lock);

	/* We have a header (pos 0) + N results to show (pos 1...N) */
	if (*_pos > local->last_scan_results_count)
		return NULL;
	return (void *)(unsigned long)(*_pos + 1); /* 0 would be EOF */
}