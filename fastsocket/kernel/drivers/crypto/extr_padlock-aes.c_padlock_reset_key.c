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
struct cword {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_cword ; 
 struct cword* per_cpu (int /*<<< orphan*/ ,int) ; 
 int raw_smp_processor_id () ; 

__attribute__((used)) static inline void padlock_reset_key(struct cword *cword)
{
	int cpu = raw_smp_processor_id();

	if (cword != per_cpu(last_cword, cpu))
#ifndef CONFIG_X86_64
		asm volatile ("pushfl; popfl");
#else
		asm volatile ("pushfq; popfq");
#endif
}