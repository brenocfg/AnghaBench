#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_9__ {scalar_t__ p_childrencnt; scalar_t__ p_stat; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_ppid; struct TYPE_9__* p_pptr; int /*<<< orphan*/  p_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  SIGCHLD ; 
 scalar_t__ SZOMB ; 
 TYPE_1__* initproc ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
proc_reparentlocked(proc_t child, proc_t parent, int signallable, int locked)
{
	proc_t oldparent = PROC_NULL;

	if (child->p_pptr == parent)
		return;

	if (locked == 0)
		proc_list_lock();

	oldparent = child->p_pptr;
#if __PROC_INTERNAL_DEBUG
	if (oldparent == PROC_NULL)
		panic("proc_reparent: process %p does not have a parent\n", child);
#endif

	LIST_REMOVE(child, p_sibling);
#if __PROC_INTERNAL_DEBUG
	if (oldparent->p_childrencnt == 0)
		panic("process children count already 0\n");
#endif
	oldparent->p_childrencnt--;
#if __PROC_INTERNAL_DEBUG1
	if (oldparent->p_childrencnt < 0)
		panic("process children count -ve\n");
#endif
	LIST_INSERT_HEAD(&parent->p_children, child, p_sibling);
	parent->p_childrencnt++;	
	child->p_pptr = parent;
	child->p_ppid = parent->p_pid;

	proc_list_unlock();

	if ((signallable != 0) && (initproc == parent) && (child->p_stat == SZOMB))
		psignal(initproc, SIGCHLD);
	if (locked == 1)
		proc_list_lock();
}