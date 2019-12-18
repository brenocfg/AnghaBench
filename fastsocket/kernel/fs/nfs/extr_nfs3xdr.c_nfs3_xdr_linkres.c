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
struct nfs3_linkres {int /*<<< orphan*/  dir_attr; int /*<<< orphan*/  fattr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_wcc_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_linkres(struct rpc_rqst *req, __be32 *p, struct nfs3_linkres *res)
{
	int	status;

	if ((status = ntohl(*p++)) != 0)
		status = nfs_stat_to_errno(status);
	p = xdr_decode_post_op_attr(p, res->fattr);
	p = xdr_decode_wcc_data(p, res->dir_attr);
	return status;
}