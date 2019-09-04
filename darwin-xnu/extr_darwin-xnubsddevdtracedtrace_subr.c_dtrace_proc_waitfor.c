#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int p_name_length; int p_pid; struct TYPE_9__* p_name; } ;
typedef  TYPE_1__ dtrace_procdesc_t ;
struct TYPE_10__ {TYPE_1__* pdesc; } ;
typedef  TYPE_2__ dtrace_proc_awaited_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  dtrace_proc_awaited_head ; 
 int /*<<< orphan*/  dtrace_proc_exec_notification ; 
 int /*<<< orphan*/ * dtrace_proc_waitfor_exec_ptr ; 
 int /*<<< orphan*/  dtrace_procwaitfor_lock ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int msleep (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int strnlen (TYPE_1__*,int) ; 

int
dtrace_proc_waitfor(dtrace_procdesc_t* pdesc) {
	dtrace_proc_awaited_entry_t entry;
	int res;

	ASSERT(pdesc);
	ASSERT(pdesc->p_name);

	/*
	 * Never trust user input, compute the length of the process name and ensure the
	 * string is null terminated.
	 */
	pdesc->p_name_length = strnlen(pdesc->p_name, sizeof(pdesc->p_name));
	if (pdesc->p_name_length >= (int) sizeof(pdesc->p_name))
		return -1;

	lck_mtx_lock(&dtrace_procwaitfor_lock);

	/* Initialize and insert the entry, then install the hook. */
	pdesc->p_pid = -1;
	entry.pdesc = pdesc;
	LIST_INSERT_HEAD(&dtrace_proc_awaited_head, &entry, entries);
	dtrace_proc_waitfor_exec_ptr = &dtrace_proc_exec_notification;

	/* Sleep until the process has been executed */
	res = msleep(&entry, &dtrace_procwaitfor_lock, PCATCH, "dtrace_proc_waitfor", NULL);

	/* Remove the entry and the hook if it is not needed anymore. */
	LIST_REMOVE(&entry, entries);
	if (LIST_EMPTY(&dtrace_proc_awaited_head))
		dtrace_proc_waitfor_exec_ptr = NULL;

	lck_mtx_unlock(&dtrace_procwaitfor_lock);

	return res;
}