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
 int /*<<< orphan*/  MAX_NUMNODES ; 
 int /*<<< orphan*/  VMCOREINFO_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_SYMBOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_level4_pgt ; 
 int /*<<< orphan*/  node_data ; 
 int /*<<< orphan*/  phys_base ; 

void arch_crash_save_vmcoreinfo(void)
{
	VMCOREINFO_SYMBOL(phys_base);
	VMCOREINFO_SYMBOL(init_level4_pgt);

#ifdef CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_data);
	VMCOREINFO_LENGTH(node_data, MAX_NUMNODES);
#endif
}