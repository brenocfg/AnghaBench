#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc_archinfo {int /*<<< orphan*/  p_cpusubtype; int /*<<< orphan*/  p_cputype; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_cpusubtype; int /*<<< orphan*/  p_cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

void 
proc_archinfo(proc_t p, struct proc_archinfo *pai)
{
	proc_lock(p);
	pai->p_cputype = p->p_cputype;
	pai->p_cpusubtype = p->p_cpusubtype;
	proc_unlock(p);
}