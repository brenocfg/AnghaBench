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
struct jffs2_sb_info {int /*<<< orphan*/  erase_completion_lock; scalar_t__ gc_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ jffs2_thread_should_wake (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void jffs2_garbage_collect_trigger(struct jffs2_sb_info *c)
{
	spin_lock(&c->erase_completion_lock);
	if (c->gc_task && jffs2_thread_should_wake(c))
		send_sig(SIGHUP, c->gc_task, 1);
	spin_unlock(&c->erase_completion_lock);
}