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
struct svc_rqst {int dummy; } ;
struct nlm_lock {int /*<<< orphan*/  len; int /*<<< orphan*/  caller; } ;
struct nlm_args {int /*<<< orphan*/  state; struct nlm_lock lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_MAXSTRLEN ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_string_inplace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nlm4svc_decode_notify(struct svc_rqst *rqstp, __be32 *p, struct nlm_args *argp)
{
	struct nlm_lock	*lock = &argp->lock;

	if (!(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len, NLM_MAXSTRLEN)))
		return 0;
	argp->state = ntohl(*p++);
	return xdr_argsize_check(rqstp, p);
}