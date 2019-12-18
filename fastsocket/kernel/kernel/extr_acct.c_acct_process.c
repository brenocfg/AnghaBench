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
struct pid_namespace {struct pid_namespace* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  acct_process_in_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  current ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

void acct_process(void)
{
	struct pid_namespace *ns;

	/*
	 * This loop is safe lockless, since current is still
	 * alive and holds its namespace, which in turn holds
	 * its parent.
	 */
	for (ns = task_active_pid_ns(current); ns != NULL; ns = ns->parent)
		acct_process_in_ns(ns);
}