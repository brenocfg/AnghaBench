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
 int /*<<< orphan*/  EHCA_PAGESIZE ; 
 int /*<<< orphan*/  H_CB_ALIGNMENT ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  ctblk_cache ; 
 int /*<<< orphan*/  ehca_cleanup_av_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_cq_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_mrmw_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_pd_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_qp_cache () ; 
 int /*<<< orphan*/  ehca_cleanup_small_qp_cache () ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 int ehca_init_av_cache () ; 
 int ehca_init_cq_cache () ; 
 int ehca_init_mrmw_cache () ; 
 int ehca_init_pd_cache () ; 
 int ehca_init_qp_cache () ; 
 int ehca_init_small_qp_cache () ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehca_create_slab_caches(void)
{
	int ret;

	ret = ehca_init_pd_cache();
	if (ret) {
		ehca_gen_err("Cannot create PD SLAB cache.");
		return ret;
	}

	ret = ehca_init_cq_cache();
	if (ret) {
		ehca_gen_err("Cannot create CQ SLAB cache.");
		goto create_slab_caches2;
	}

	ret = ehca_init_qp_cache();
	if (ret) {
		ehca_gen_err("Cannot create QP SLAB cache.");
		goto create_slab_caches3;
	}

	ret = ehca_init_av_cache();
	if (ret) {
		ehca_gen_err("Cannot create AV SLAB cache.");
		goto create_slab_caches4;
	}

	ret = ehca_init_mrmw_cache();
	if (ret) {
		ehca_gen_err("Cannot create MR&MW SLAB cache.");
		goto create_slab_caches5;
	}

	ret = ehca_init_small_qp_cache();
	if (ret) {
		ehca_gen_err("Cannot create small queue SLAB cache.");
		goto create_slab_caches6;
	}

#ifdef CONFIG_PPC_64K_PAGES
	ctblk_cache = kmem_cache_create("ehca_cache_ctblk",
					EHCA_PAGESIZE, H_CB_ALIGNMENT,
					SLAB_HWCACHE_ALIGN,
					NULL);
	if (!ctblk_cache) {
		ehca_gen_err("Cannot create ctblk SLAB cache.");
		ehca_cleanup_small_qp_cache();
		goto create_slab_caches6;
	}
#endif
	return 0;

create_slab_caches6:
	ehca_cleanup_mrmw_cache();

create_slab_caches5:
	ehca_cleanup_av_cache();

create_slab_caches4:
	ehca_cleanup_qp_cache();

create_slab_caches3:
	ehca_cleanup_cq_cache();

create_slab_caches2:
	ehca_cleanup_pd_cache();

	return ret;
}