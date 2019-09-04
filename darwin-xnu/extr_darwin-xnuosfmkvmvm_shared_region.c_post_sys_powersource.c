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
 int /*<<< orphan*/  post_sys_powersource_internal (int,int /*<<< orphan*/ ) ; 

void
#if defined(__i386__) || defined(__x86_64__)
post_sys_powersource(int i)
#else
post_sys_powersource(__unused int i)
#endif
{
#if defined(__i386__) || defined(__x86_64__)
	post_sys_powersource_internal(i, 0);
#endif /* __i386__ || __x86_64__ */
}