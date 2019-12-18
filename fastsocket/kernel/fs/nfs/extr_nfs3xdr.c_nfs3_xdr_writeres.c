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
struct nfs_writeres {int count; TYPE_1__* verf; int /*<<< orphan*/  fattr; } ;
typedef  enum nfs3_stable_how { ____Placeholder_nfs3_stable_how } nfs3_stable_how ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int committed; int /*<<< orphan*/ * verifier; } ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_wcc_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_writeres(struct rpc_rqst *req, __be32 *p, struct nfs_writeres *res)
{
	int	status;

	status = ntohl(*p++);
	p = xdr_decode_wcc_data(p, res->fattr);

	if (status != 0)
		return nfs_stat_to_errno(status);

	res->count = ntohl(*p++);
	res->verf->committed = (enum nfs3_stable_how)ntohl(*p++);
	res->verf->verifier[0] = *p++;
	res->verf->verifier[1] = *p++;

	return res->count;
}