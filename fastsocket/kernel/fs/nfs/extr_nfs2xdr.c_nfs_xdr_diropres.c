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
struct nfs_diropok {int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_decode_fattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_diropres(struct rpc_rqst *req, __be32 *p, struct nfs_diropok *res)
{
	int	status;

	if ((status = ntohl(*p++)))
		return nfs_stat_to_errno(status);
	p = xdr_decode_fhandle(p, res->fh);
	xdr_decode_fattr(p, res->fattr);
	return 0;
}