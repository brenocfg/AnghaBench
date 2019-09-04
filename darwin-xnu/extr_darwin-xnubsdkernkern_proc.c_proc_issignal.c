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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_NULL ; 
 int /*<<< orphan*/  proc_find (int) ; 
 int proc_pendingsignals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ ) ; 

int
proc_issignal(int pid, sigset_t mask)
{
	proc_t p;
	int error=0;

	if ((p = proc_find(pid)) != PROC_NULL) {
		error = proc_pendingsignals(p, mask);
		proc_rele(p);
	}	

	return(error);
}