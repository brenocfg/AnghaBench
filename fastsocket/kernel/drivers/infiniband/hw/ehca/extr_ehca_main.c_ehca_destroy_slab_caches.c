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
 scalar_t__ ctblk_cache ; 
 int /*<<< orphan*/  ehca_cleanup_av_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_cq_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_mrmw_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_pd_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_qp_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_small_qp_cache () ; 
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 

__attribute__((used)) static void ehca_destroy_slab_caches(void)
{
	ehca_cleanup_small_qp_cache();
	ehca_cleanup_mrmw_cache();
	ehca_cleanup_av_cache();
	ehca_cleanup_qp_cache();
	ehca_cleanup_cq_cache();
	ehca_cleanup_pd_cache();
#ifdef CONFIG_PPC_64K_PAGES
	if (ctblk_cache)
		kmem_cache_destroy(ctblk_cache);
#endif
}