#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct svc_rqst {int dummy; } ;
struct TYPE_5__ {scalar_t__ fl_pid; } ;
struct nlm_lock {int /*<<< orphan*/  oh; int /*<<< orphan*/  fh; int /*<<< orphan*/  len; int /*<<< orphan*/  caller; scalar_t__ svid; TYPE_3__ fl; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {void* fsm_access; void* fsm_mode; int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;
typedef  TYPE_1__ nlm_args ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_MAXSTRLEN ; 
 int /*<<< orphan*/  locks_init_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (struct nlm_lock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nlm4_decode_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm4_decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nlm4_decode_oh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_string_inplace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nlm4svc_decode_shareargs(struct svc_rqst *rqstp, __be32 *p, nlm_args *argp)
{
	struct nlm_lock	*lock = &argp->lock;

	memset(lock, 0, sizeof(*lock));
	locks_init_lock(&lock->fl);
	lock->svid = ~(u32) 0;
	lock->fl.fl_pid = (pid_t)lock->svid;

	if (!(p = nlm4_decode_cookie(p, &argp->cookie))
	 || !(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len, NLM_MAXSTRLEN))
	 || !(p = nlm4_decode_fh(p, &lock->fh))
	 || !(p = nlm4_decode_oh(p, &lock->oh)))
		return 0;
	argp->fsm_mode = ntohl(*p++);
	argp->fsm_access = ntohl(*p++);
	return xdr_argsize_check(rqstp, p);
}