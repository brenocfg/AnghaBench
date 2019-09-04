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

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int _NSIG ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  app_mask ; 

void __block_app_sigs(void *set)
{
	__syscall(SYS_rt_sigprocmask, SIG_BLOCK, &app_mask, set, _NSIG/8);
}