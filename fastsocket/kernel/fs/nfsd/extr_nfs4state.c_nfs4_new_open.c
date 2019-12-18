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
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct nfsd4_open {int /*<<< orphan*/  op_share_access; } ;
struct nfs4_stateid {int dummy; } ;
struct nfs4_file {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_stateid*) ; 
 struct nfs4_stateid* nfs4_alloc_stateid () ; 
 scalar_t__ nfs4_get_vfs_file (struct svc_rqst*,struct nfs4_file*,struct svc_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_resource ; 
 int /*<<< orphan*/  stateid_slab ; 

__attribute__((used)) static __be32
nfs4_new_open(struct svc_rqst *rqstp, struct nfs4_stateid **stpp,
		struct nfs4_file *fp, struct svc_fh *cur_fh,
		struct nfsd4_open *open)
{
	struct nfs4_stateid *stp;
	__be32 status;

	stp = nfs4_alloc_stateid();
	if (stp == NULL)
		return nfserr_resource;

	status = nfs4_get_vfs_file(rqstp, fp, cur_fh, open->op_share_access);
	if (status) {
		kmem_cache_free(stateid_slab, stp);
		return status;
	}
	*stpp = stp;
	return 0;
}