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
typedef  int /*<<< orphan*/  uthread_t ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_uthread_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mach_kauth_cred_uthread_update(void)
{
	uthread_t uthread;
	proc_t proc;

	uthread = get_bsdthread_info(current_thread());
	proc = current_proc();

	kauth_cred_uthread_update(uthread, proc);
}