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
struct nlm_res {int dummy; } ;
struct nlm_args {scalar_t__ monitor; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nlmsvc_proc_lock (struct svc_rqst*,struct nlm_args*,struct nlm_res*) ; 

__attribute__((used)) static __be32
nlmsvc_proc_nm_lock(struct svc_rqst *rqstp, struct nlm_args *argp,
				            struct nlm_res  *resp)
{
	dprintk("lockd: NM_LOCK       called\n");

	argp->monitor = 0;		/* just clean the monitor flag */
	return nlmsvc_proc_lock(rqstp, argp, resp);
}