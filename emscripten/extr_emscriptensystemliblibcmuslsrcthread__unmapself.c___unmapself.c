#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTJMP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_set_tid_address ; 
 TYPE_1__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ a_cas (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  a_spin () ; 
 int /*<<< orphan*/  do_unmap ; 
 scalar_t__ lock ; 
 char* shared_stack ; 
 void* unmap_base ; 
 size_t unmap_size ; 

void __unmapself(void *base, size_t size)
{
	int tid=__pthread_self()->tid;
	char *stack = shared_stack + sizeof shared_stack;
	stack -= (uintptr_t)stack % 16;
	while (lock || a_cas(&lock, 0, tid))
		a_spin();
	__syscall(SYS_set_tid_address, &lock);
	unmap_base = base;
	unmap_size = size;
	CRTJMP(do_unmap, stack);
}