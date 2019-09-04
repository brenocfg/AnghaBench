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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_NULL ; 
 int /*<<< orphan*/  proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psignal (int /*<<< orphan*/ ,int) ; 

void
proc_signal(int pid, int signum)
{
	proc_t p;

	if ((p = proc_find(pid)) != PROC_NULL) {
			psignal(p, signum);
			proc_rele(p);
	}	
}