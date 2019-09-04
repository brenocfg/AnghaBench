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

void
nfs_gss_init(void)
{
#if NFSCLIENT
	nfs_gss_clnt_grp = lck_grp_alloc_init("rpcsec_gss_clnt", LCK_GRP_ATTR_NULL);
#endif /* NFSCLIENT */

#if NFSSERVER
	nfs_gss_svc_grp  = lck_grp_alloc_init("rpcsec_gss_svc",  LCK_GRP_ATTR_NULL);

	nfs_gss_svc_ctx_hashtbl = hashinit(SVC_CTX_HASHSZ, M_TEMP, &nfs_gss_svc_ctx_hash);
	nfs_gss_svc_ctx_mutex = lck_mtx_alloc_init(nfs_gss_svc_grp, LCK_ATTR_NULL);

	nfs_gss_svc_ctx_timer_call = thread_call_allocate(nfs_gss_svc_ctx_timer, NULL);
#endif /* NFSSERVER */
}