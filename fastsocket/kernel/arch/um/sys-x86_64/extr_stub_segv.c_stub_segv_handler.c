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
struct ucontext {int /*<<< orphan*/  uc_mcontext; } ;
struct faultinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FAULTINFO_FROM_SC (struct faultinfo,int /*<<< orphan*/ *) ; 
 scalar_t__ STUB_DATA ; 
 int /*<<< orphan*/  trap_myself () ; 

void __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(int sig)
{
	struct ucontext *uc;

	__asm__ __volatile__("movq %%rdx, %0" : "=g" (uc) :);
	GET_FAULTINFO_FROM_SC(*((struct faultinfo *) STUB_DATA),
			      &uc->uc_mcontext);
	trap_myself();
}