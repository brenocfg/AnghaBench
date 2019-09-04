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
struct fileproc {scalar_t__ f_flag; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int) ; 
 int /*<<< orphan*/  proc_fdlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

int
file_flags(int fd, int *flags)
{

	proc_t p = current_proc();
	struct fileproc *fp;
	int error;

	proc_fdlock_spin(p);
	if ( (error = fp_lookup(p, fd, &fp, 1)) ) {
		proc_fdunlock(p);
		return(error);
	}
	*flags = (int)fp->f_flag;
	fp_drop(p, fd, fp,1);
	proc_fdunlock(p);

	return(0);
}