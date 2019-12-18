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
struct pktgen_thread {int /*<<< orphan*/  th_list; TYPE_1__* tsk; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_proc_dir ; 
 int /*<<< orphan*/  pktgen_thread_lock ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pktgen_rem_thread(struct pktgen_thread *t)
{
	/* Remove from the thread list */

	remove_proc_entry(t->tsk->comm, pg_proc_dir);

	mutex_lock(&pktgen_thread_lock);

	list_del(&t->th_list);

	mutex_unlock(&pktgen_thread_lock);
}