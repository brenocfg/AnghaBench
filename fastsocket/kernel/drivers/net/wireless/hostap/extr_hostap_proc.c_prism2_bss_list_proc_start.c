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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  bss_list; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 void* seq_list_start_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *prism2_bss_list_proc_start(struct seq_file *m, loff_t *_pos)
{
	local_info_t *local = m->private;
	spin_lock_bh(&local->lock);
	return seq_list_start_head(&local->bss_list, *_pos);
}