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
 int /*<<< orphan*/  IA64_CMCP_VECTOR ; 
 int /*<<< orphan*/  IA64_IPI_DM_INT ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  first_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_send_ipi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_mca_cmc_poll (unsigned long dummy)
{
	/* Trigger a CMC interrupt cascade  */
	platform_send_ipi(first_cpu(cpu_online_map), IA64_CMCP_VECTOR, IA64_IPI_DM_INT, 0);
}