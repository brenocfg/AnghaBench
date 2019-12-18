#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_rqst {int /*<<< orphan*/  rq_svec; int /*<<< orphan*/  rq_slen; } ;
struct nfs_renameargs {TYPE_1__* new_name; int /*<<< orphan*/  new_dir; TYPE_2__* old_name; int /*<<< orphan*/  old_dir; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_adjust_iovec (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_fhandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs3_xdr_renameargs(struct rpc_rqst *req, __be32 *p, struct nfs_renameargs *args)
{
	p = xdr_encode_fhandle(p, args->old_dir);
	p = xdr_encode_array(p, args->old_name->name, args->old_name->len);
	p = xdr_encode_fhandle(p, args->new_dir);
	p = xdr_encode_array(p, args->new_name->name, args->new_name->len);
	req->rq_slen = xdr_adjust_iovec(req->rq_svec, p);
	return 0;
}