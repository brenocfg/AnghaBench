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
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  se_sess_cache ; 
 int /*<<< orphan*/  se_ua_cache ; 
 int /*<<< orphan*/  t10_alua_lu_gp_cache ; 
 int /*<<< orphan*/  t10_alua_lu_gp_mem_cache ; 
 int /*<<< orphan*/  t10_alua_tg_pt_gp_cache ; 
 int /*<<< orphan*/  t10_alua_tg_pt_gp_mem_cache ; 
 int /*<<< orphan*/  t10_pr_reg_cache ; 
 int /*<<< orphan*/  target_completion_wq ; 

void release_se_kmem_caches(void)
{
	destroy_workqueue(target_completion_wq);
	kmem_cache_destroy(se_sess_cache);
	kmem_cache_destroy(se_ua_cache);
	kmem_cache_destroy(t10_pr_reg_cache);
	kmem_cache_destroy(t10_alua_lu_gp_cache);
	kmem_cache_destroy(t10_alua_lu_gp_mem_cache);
	kmem_cache_destroy(t10_alua_tg_pt_gp_cache);
	kmem_cache_destroy(t10_alua_tg_pt_gp_mem_cache);
}