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
struct rpc_rqst {int dummy; } ;
struct nfs_removeres {int /*<<< orphan*/  dir_attr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs3_xdr_wccstat (struct rpc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_removeres(struct rpc_rqst *req, __be32 *p, struct nfs_removeres *res)
{
	return nfs3_xdr_wccstat(req, p, res->dir_attr);
}