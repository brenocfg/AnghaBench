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
struct fileproc {int /*<<< orphan*/  f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdrelse (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fg_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileproc_free (struct fileproc*) ; 
 int /*<<< orphan*/  proc_fdlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 

int
fp_free(proc_t p, int fd, struct fileproc * fp)
{
        proc_fdlock_spin(p);
	fdrelse(p, fd);
        proc_fdunlock(p);

	fg_free(fp->f_fglob);
	fileproc_free(fp);
	return(0);
}