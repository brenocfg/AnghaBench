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
 int /*<<< orphan*/  SYS_rt_sigsuspend ; 
 int _NSIG ; 
 int syscall_cp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int sigsuspend(const sigset_t *mask)
{
	return syscall_cp(SYS_rt_sigsuspend, mask, _NSIG/8);
}