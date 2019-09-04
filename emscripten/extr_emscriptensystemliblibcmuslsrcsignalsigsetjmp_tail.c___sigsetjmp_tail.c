#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sigjmp_buf ;
struct TYPE_3__ {void* __ss; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int _NSIG ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int) ; 

__attribute__((__visibility__("hidden")))
int __sigsetjmp_tail(sigjmp_buf jb, int ret)
{
	void *p = jb->__ss;
	__syscall(SYS_rt_sigprocmask, SIG_SETMASK, ret?p:0, ret?0:p, _NSIG/8);
	return ret;
}