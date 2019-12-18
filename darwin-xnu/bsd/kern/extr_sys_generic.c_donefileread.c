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
struct fileproc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  proc_fdlock_spin (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 

void
donefileread(struct proc *p, struct fileproc *fp, int fd)
{
	proc_fdlock_spin(p);
	fp_drop(p, fd, fp, 1);
        proc_fdunlock(p);
}