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
struct nfs_pathconf {void* max_namelen; void* max_link; int /*<<< orphan*/  fattr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_pathconfres(struct rpc_rqst *req, __be32 *p, struct nfs_pathconf *res)
{
	int		status;

	status = ntohl(*p++);

	p = xdr_decode_post_op_attr(p, res->fattr);
	if (status != 0)
		return nfs_stat_to_errno(status);
	res->max_link = ntohl(*p++);
	res->max_namelen = ntohl(*p++);

	/* ignore remaining fields */
	return 0;
}