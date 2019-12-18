#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct nfsmount {TYPE_1__* nm_funcs; } ;
struct nfs_vattr {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_namelen; } ;
struct TYPE_22__ {int /*<<< orphan*/  r_auth; } ;
struct nfs_dulookup {int du_flags; TYPE_11__ du_cn; int /*<<< orphan*/  du_smallname; TYPE_5__ du_req; } ;
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_21__ {int /*<<< orphan*/  fh_len; int /*<<< orphan*/  fh_data; } ;
typedef  TYPE_3__ fhandle_t ;
struct TYPE_20__ {int /*<<< orphan*/  n_flag; } ;
struct TYPE_19__ {int (* nf_lookup_rpc_async_finish ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,struct nfs_vattr*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  NFSTOMP (TYPE_2__*) ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 int NFS_DULOOKUP_INPROG ; 
 int /*<<< orphan*/  NG_MAKEENTRY ; 
 int /*<<< orphan*/  NNEGNCENTRIES ; 
 int /*<<< orphan*/  NVATTR_CLEANUP (struct nfs_vattr*) ; 
 int /*<<< orphan*/  NVATTR_INIT (struct nfs_vattr*) ; 
 int /*<<< orphan*/  cache_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_11__*) ; 
 int nfs_nget (int /*<<< orphan*/ ,TYPE_2__*,TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs_vattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  nfs_request_async_cancel (TYPE_5__*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,struct nfs_vattr*) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 

void
nfs_dulookup_finish(struct nfs_dulookup *dulp, nfsnode_t dnp, vfs_context_t ctx)
{
	struct nfsmount *nmp = NFSTONMP(dnp);
	int error;
	nfsnode_t du_np;
	u_int64_t xid;
	fhandle_t fh;
	struct nfs_vattr nvattr;

	if (!nmp || !(dulp->du_flags & NFS_DULOOKUP_INPROG))
		goto out;

	NVATTR_INIT(&nvattr);
	error = nmp->nm_funcs->nf_lookup_rpc_async_finish(dnp, dulp->du_cn.cn_nameptr,
			dulp->du_cn.cn_namelen, ctx, &dulp->du_req, &xid, &fh, &nvattr);
	dulp->du_flags &= ~NFS_DULOOKUP_INPROG;
	if (error == ENOENT) {
		/* add a negative entry in the name cache */
		nfs_node_lock_force(dnp);
		cache_enter(NFSTOV(dnp), NULL, &dulp->du_cn);
		dnp->n_flag |= NNEGNCENTRIES;
		nfs_node_unlock(dnp);
	} else if (!error) {
		error = nfs_nget(NFSTOMP(dnp), dnp, &dulp->du_cn, fh.fh_data, fh.fh_len,
			    &nvattr, &xid, dulp->du_req.r_auth, NG_MAKEENTRY, &du_np);
		if (!error) {
			nfs_node_unlock(du_np);
			vnode_put(NFSTOV(du_np));
		}
	}
	NVATTR_CLEANUP(&nvattr);
out:
	if (dulp->du_flags & NFS_DULOOKUP_INPROG)
		nfs_request_async_cancel(&dulp->du_req);
	if (dulp->du_cn.cn_nameptr && (dulp->du_cn.cn_nameptr != dulp->du_smallname))
		FREE(dulp->du_cn.cn_nameptr, M_TEMP);
}