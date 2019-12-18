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
struct TYPE_4__ {int /*<<< orphan*/  page_len; int /*<<< orphan*/  pages; TYPE_1__* head; } ;
struct svc_rqst {TYPE_2__ rq_arg; } ;
struct nfsd4_compoundargs {struct svc_rqst* rqstp; int /*<<< orphan*/  iops; int /*<<< orphan*/  ops; int /*<<< orphan*/ * to_free; int /*<<< orphan*/ * tmpp; int /*<<< orphan*/  pagelen; int /*<<< orphan*/  pagelist; scalar_t__ end; scalar_t__* p; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {scalar_t__ iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 scalar_t__ nfsd4_decode_compound (struct nfsd4_compoundargs*) ; 
 int /*<<< orphan*/  nfsd4_release_compoundargs (struct nfsd4_compoundargs*) ; 

int
nfs4svc_decode_compoundargs(struct svc_rqst *rqstp, __be32 *p, struct nfsd4_compoundargs *args)
{
	__be32 status;

	args->p = p;
	args->end = rqstp->rq_arg.head[0].iov_base + rqstp->rq_arg.head[0].iov_len;
	args->pagelist = rqstp->rq_arg.pages;
	args->pagelen = rqstp->rq_arg.page_len;
	args->tmpp = NULL;
	args->to_free = NULL;
	args->ops = args->iops;
	args->rqstp = rqstp;

	status = nfsd4_decode_compound(args);
	if (status) {
		nfsd4_release_compoundargs(args);
	}
	return !status;
}