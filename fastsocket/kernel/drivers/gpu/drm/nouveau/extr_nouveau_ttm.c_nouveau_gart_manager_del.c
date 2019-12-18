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
struct ttm_mem_type_manager {int dummy; } ;
struct ttm_mem_reg {int /*<<< orphan*/ * mm_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mem_node_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_gart_manager_del(struct ttm_mem_type_manager *man,
			 struct ttm_mem_reg *mem)
{
	nouveau_mem_node_cleanup(mem->mm_node);
	kfree(mem->mm_node);
	mem->mm_node = NULL;
}