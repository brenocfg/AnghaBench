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
 int /*<<< orphan*/  IA64_IPI_DM_INT ; 
 int /*<<< orphan*/  IA64_IPI_LOCAL_TLB_FLUSH ; 
 int /*<<< orphan*/  platform_send_ipi (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smp_send_local_flush_tlb (int cpu)
{
	platform_send_ipi(cpu, IA64_IPI_LOCAL_TLB_FLUSH, IA64_IPI_DM_INT, 0);
}