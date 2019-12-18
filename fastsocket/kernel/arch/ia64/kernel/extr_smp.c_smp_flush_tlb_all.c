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
 scalar_t__ local_flush_tlb_all ; 
 int /*<<< orphan*/  on_each_cpu (void (*) (void*),int /*<<< orphan*/ *,int) ; 

void
smp_flush_tlb_all (void)
{
	on_each_cpu((void (*)(void *))local_flush_tlb_all, NULL, 1);
}