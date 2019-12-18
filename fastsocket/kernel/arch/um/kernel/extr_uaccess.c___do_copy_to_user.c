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
typedef  int /*<<< orphan*/  jmp_buf ;

/* Variables and functions */
 int /*<<< orphan*/  __do_copy ; 
 unsigned long __do_user_copy (void*,void const*,int,void**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*) ; 

int __do_copy_to_user(void *to, const void *from, int n,
		      void **fault_addr, jmp_buf **fault_catcher)
{
	unsigned long fault;
	int faulted;

	fault = __do_user_copy(to, from, n, fault_addr, fault_catcher,
			       __do_copy, &faulted);
	if (!faulted)
		return 0;
	else
		return n - (fault - (unsigned long) to);
}