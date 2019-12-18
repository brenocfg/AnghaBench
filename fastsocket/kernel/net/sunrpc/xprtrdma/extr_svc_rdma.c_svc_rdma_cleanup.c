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
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_class ; 
 int /*<<< orphan*/  svc_rdma_ctxt_cachep ; 
 int /*<<< orphan*/  svc_rdma_map_cachep ; 
 int /*<<< orphan*/  svc_unreg_xprt_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svcrdma_table_header ; 
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ *) ; 

void svc_rdma_cleanup(void)
{
	dprintk("SVCRDMA Module Removed, deregister RPC RDMA transport\n");
	flush_scheduled_work();
	if (svcrdma_table_header) {
		unregister_sysctl_table(svcrdma_table_header);
		svcrdma_table_header = NULL;
	}
	svc_unreg_xprt_class(&svc_rdma_class);
	kmem_cache_destroy(svc_rdma_map_cachep);
	kmem_cache_destroy(svc_rdma_ctxt_cachep);
}