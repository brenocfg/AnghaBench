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
struct sys_cfg_data {struct eachquadmem* eq; } ;
struct eachquadmem {scalar_t__ hi_shrd_mem_size; scalar_t__ hi_shrd_mem_start; scalar_t__ priv_mem_size; } ;

/* Variables and functions */
 void* MB_TO_PAGES (scalar_t__) ; 
 int /*<<< orphan*/  e820_register_active_regions (int,void*,void*) ; 
 int /*<<< orphan*/  memory_present (int,void*,void*) ; 
 void** node_end_pfn ; 
 int /*<<< orphan*/  node_memmap_size_bytes (int,void*,void*) ; 
 int /*<<< orphan*/ * node_remap_size ; 
 int /*<<< orphan*/  node_set_online (int) ; 
 void** node_start_pfn ; 

__attribute__((used)) static inline void numaq_register_node(int node, struct sys_cfg_data *scd)
{
	struct eachquadmem *eq = scd->eq + node;

	node_set_online(node);

	/* Convert to pages */
	node_start_pfn[node] =
		 MB_TO_PAGES(eq->hi_shrd_mem_start - eq->priv_mem_size);

	node_end_pfn[node] =
		 MB_TO_PAGES(eq->hi_shrd_mem_start + eq->hi_shrd_mem_size);

	e820_register_active_regions(node, node_start_pfn[node],
						node_end_pfn[node]);

	memory_present(node, node_start_pfn[node], node_end_pfn[node]);

	node_remap_size[node] = node_memmap_size_bytes(node,
					node_start_pfn[node],
					node_end_pfn[node]);
}