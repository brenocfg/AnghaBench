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
struct nfs_fsstat {int /*<<< orphan*/  afiles; int /*<<< orphan*/  ffiles; int /*<<< orphan*/  tfiles; int /*<<< orphan*/  abytes; int /*<<< orphan*/  fbytes; int /*<<< orphan*/  tbytes; int /*<<< orphan*/  fattr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_fsstatres(struct rpc_rqst *req, __be32 *p, struct nfs_fsstat *res)
{
	int		status;

	status = ntohl(*p++);

	p = xdr_decode_post_op_attr(p, res->fattr);
	if (status != 0)
		return nfs_stat_to_errno(status);

	p = xdr_decode_hyper(p, &res->tbytes);
	p = xdr_decode_hyper(p, &res->fbytes);
	p = xdr_decode_hyper(p, &res->abytes);
	p = xdr_decode_hyper(p, &res->tfiles);
	p = xdr_decode_hyper(p, &res->ffiles);
	p = xdr_decode_hyper(p, &res->afiles);

	/* ignore invarsec */
	return 0;
}