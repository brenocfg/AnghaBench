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
struct fileproc {int /*<<< orphan*/  f_flags; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  FP_WAITEVENT ; 
 int fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int /*<<< orphan*/  proc_fdlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

int
fp_drop_event(proc_t p, int fd, struct fileproc *fp)
{
        int error;

	proc_fdlock_spin(p);

	fp->f_flags |= FP_WAITEVENT;

	error = fp_drop(p, fd, fp, 1);

	proc_fdunlock(p);

	return (error);
}