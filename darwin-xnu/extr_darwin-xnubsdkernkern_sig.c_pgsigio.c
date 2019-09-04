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
typedef  scalar_t__ proc_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 scalar_t__ PROC_NULL ; 
 int /*<<< orphan*/  gsignal (int /*<<< orphan*/ ,int) ; 
 scalar_t__ proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 
 int /*<<< orphan*/  psignal (scalar_t__,int) ; 

void
pgsigio(pid_t pgid, int sig)
{ 
	proc_t p = PROC_NULL;

	if (pgid < 0) 
		gsignal(-(pgid), sig);

	else if (pgid > 0 && (p = proc_find(pgid)) != 0) 
		psignal(p, sig);
	if (p != PROC_NULL)
		proc_rele(p);
}