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
struct nfs3_diropres {int /*<<< orphan*/  dir_attr; int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int errno_NFSERR_IO ; 
 int nfs_stat_to_errno (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_lookupres(struct rpc_rqst *req, __be32 *p, struct nfs3_diropres *res)
{
	int	status;

	if ((status = ntohl(*p++))) {
		status = nfs_stat_to_errno(status);
	} else {
		if (!(p = xdr_decode_fhandle(p, res->fh)))
			return -errno_NFSERR_IO;
		p = xdr_decode_post_op_attr(p, res->fattr);
	}
	xdr_decode_post_op_attr(p, res->dir_attr);
	return status;
}