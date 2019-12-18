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
 int /*<<< orphan*/  NR_NODE_MEMBLKS ; 
 int /*<<< orphan*/  PGTABLE_3 ; 
 int /*<<< orphan*/  PGTABLE_4 ; 
 int /*<<< orphan*/  VMCOREINFO_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_STRUCT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCOREINFO_SYMBOL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_memblk ; 
 int /*<<< orphan*/  node_memblk_s ; 
 int /*<<< orphan*/  pgdat_list ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  start_paddr ; 

void arch_crash_save_vmcoreinfo(void)
{
#if defined(CONFIG_DISCONTIGMEM) || defined(CONFIG_SPARSEMEM)
	VMCOREINFO_SYMBOL(pgdat_list);
	VMCOREINFO_LENGTH(pgdat_list, MAX_NUMNODES);
#endif
#ifdef CONFIG_NUMA
	VMCOREINFO_SYMBOL(node_memblk);
	VMCOREINFO_LENGTH(node_memblk, NR_NODE_MEMBLKS);
	VMCOREINFO_STRUCT_SIZE(node_memblk_s);
	VMCOREINFO_OFFSET(node_memblk_s, start_paddr);
	VMCOREINFO_OFFSET(node_memblk_s, size);
#endif
#ifdef CONFIG_PGTABLE_3
	VMCOREINFO_CONFIG(PGTABLE_3);
#elif  CONFIG_PGTABLE_4
	VMCOREINFO_CONFIG(PGTABLE_4);
#endif
}