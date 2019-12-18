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
struct pgrp {int dummy; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_listflag; int /*<<< orphan*/  p_children; int /*<<< orphan*/  p_childrencnt; scalar_t__ p_xhighbits; int /*<<< orphan*/  p_uniqueid; int /*<<< orphan*/  p_puniqueid; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_ppid; struct TYPE_9__* p_pptr; int /*<<< orphan*/  p_evlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LIST_INCREATE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  allproc ; 
 int /*<<< orphan*/  memorystatus_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_list ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  pg_rele (struct pgrp*) ; 
 int /*<<< orphan*/  pgrp_add (struct pgrp*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 struct pgrp* proc_pgrp (TYPE_1__*) ; 

void
pinsertchild(proc_t parent, proc_t child)
{
	struct pgrp * pg;

	LIST_INIT(&child->p_children);
	TAILQ_INIT(&child->p_evlist);
	child->p_pptr = parent;
	child->p_ppid = parent->p_pid;
	child->p_puniqueid = parent->p_uniqueid;
	child->p_xhighbits = 0;

	pg = proc_pgrp(parent);
	pgrp_add(pg, parent, child);
	pg_rele(pg);

	proc_list_lock();
	
#if CONFIG_MEMORYSTATUS
	memorystatus_add(child, TRUE);
#endif
	
	parent->p_childrencnt++;
	LIST_INSERT_HEAD(&parent->p_children, child, p_sibling);

	LIST_INSERT_HEAD(&allproc, child, p_list);
	/* mark the completion of proc creation */
	child->p_listflag &= ~P_LIST_INCREATE;

	proc_list_unlock();
}