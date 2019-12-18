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
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_call_function (void (*) (void*),void*,int) ; 

__attribute__((used)) static inline void cacheop_on_each_cpu(void (*func) (void *info), void *info,
                                   int wait)
{
	preempt_disable();
	smp_call_function(func, info, wait);
	func(info);
	preempt_enable();
}