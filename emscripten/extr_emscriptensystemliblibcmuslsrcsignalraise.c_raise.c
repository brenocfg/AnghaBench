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

/* Variables and functions */
 int /*<<< orphan*/  SYS_gettid ; 
 int /*<<< orphan*/  SYS_tkill ; 
 int /*<<< orphan*/  __block_app_sigs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __restore_sigs (int /*<<< orphan*/ *) ; 
 int __syscall (int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,int,int) ; 

int raise(int sig)
{
	int tid, ret;
	sigset_t set;
	__block_app_sigs(&set);
	tid = __syscall(SYS_gettid);
	ret = syscall(SYS_tkill, tid, sig);
	__restore_sigs(&set);
	return ret;
}