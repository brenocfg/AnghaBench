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
struct nfs_fsinfo {scalar_t__ lease_time; int /*<<< orphan*/  time_delta; int /*<<< orphan*/  maxfilesize; void* dtpref; void* wtmult; void* wtpref; void* wtmax; void* rtmult; void* rtpref; void* rtmax; int /*<<< orphan*/  fattr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs3_xdr_fsinfores(struct rpc_rqst *req, __be32 *p, struct nfs_fsinfo *res)
{
	int		status;

	status = ntohl(*p++);

	p = xdr_decode_post_op_attr(p, res->fattr);
	if (status != 0)
		return nfs_stat_to_errno(status);

	res->rtmax  = ntohl(*p++);
	res->rtpref = ntohl(*p++);
	res->rtmult = ntohl(*p++);
	res->wtmax  = ntohl(*p++);
	res->wtpref = ntohl(*p++);
	res->wtmult = ntohl(*p++);
	res->dtpref = ntohl(*p++);
	p = xdr_decode_hyper(p, &res->maxfilesize);
	p = xdr_decode_time3(p, &res->time_delta);

	/* ignore properties */
	res->lease_time = 0;
	return 0;
}