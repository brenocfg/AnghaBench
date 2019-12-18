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
struct nfs2_fsstat {void* bavail; void* bfree; void* blocks; void* bsize; void* tsize; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int nfs_stat_to_errno (int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_xdr_statfsres(struct rpc_rqst *req, __be32 *p, struct nfs2_fsstat *res)
{
	int	status;

	if ((status = ntohl(*p++)))
		return nfs_stat_to_errno(status);

	res->tsize  = ntohl(*p++);
	res->bsize  = ntohl(*p++);
	res->blocks = ntohl(*p++);
	res->bfree  = ntohl(*p++);
	res->bavail = ntohl(*p++);
	return 0;
}