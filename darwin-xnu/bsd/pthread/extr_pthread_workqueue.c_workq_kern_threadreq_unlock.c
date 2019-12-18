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
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_get_wqptr_fast (struct proc*) ; 
 int /*<<< orphan*/  workq_unlock (int /*<<< orphan*/ ) ; 

void
workq_kern_threadreq_unlock(struct proc *p)
{
	workq_unlock(proc_get_wqptr_fast(p));
}