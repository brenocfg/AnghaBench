#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_rqst {int dummy; } ;
struct nfs_writeres {int /*<<< orphan*/  fattr; TYPE_1__* verf; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  committed; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FILE_SYNC ; 
 int nfs_xdr_attrstat (struct rpc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_writeres(struct rpc_rqst *req, __be32 *p, struct nfs_writeres *res)
{
	res->verf->committed = NFS_FILE_SYNC;
	return nfs_xdr_attrstat(req, p, res->fattr);
}