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
 int CL_DIRECT_READ_LOCK_BUCKETS ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_direct_read_locks ; 
 int /*<<< orphan*/  cl_direct_read_spin_lock ; 
 int /*<<< orphan*/  cl_mtx_attr ; 
 int /*<<< orphan*/  cl_mtx_grp ; 
 int /*<<< orphan*/  cl_mtx_grp_attr ; 
 int /*<<< orphan*/ * cl_transaction_mtxp ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/ * lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
cluster_init(void) {
        /*
	 * allocate lock group attribute and group
	 */
        cl_mtx_grp_attr = lck_grp_attr_alloc_init();
	cl_mtx_grp = lck_grp_alloc_init("cluster I/O", cl_mtx_grp_attr);
		
	/*
	 * allocate the lock attribute
	 */
	cl_mtx_attr = lck_attr_alloc_init();

	cl_transaction_mtxp = lck_mtx_alloc_init(cl_mtx_grp, cl_mtx_attr);

	if (cl_transaction_mtxp == NULL)
	        panic("cluster_init: failed to allocate cl_transaction_mtxp");

	lck_spin_init(&cl_direct_read_spin_lock, cl_mtx_grp, cl_mtx_attr);

	for (int i = 0; i < CL_DIRECT_READ_LOCK_BUCKETS; ++i)
		LIST_INIT(&cl_direct_read_locks[i]);
}