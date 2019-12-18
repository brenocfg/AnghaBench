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
struct svc_xprt {int /*<<< orphan*/  xpt_local; int /*<<< orphan*/  xpt_remotelen; int /*<<< orphan*/  xpt_remote; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr; } ;
struct svc_rqst {TYPE_1__ rq_daddr; int /*<<< orphan*/  rq_addrlen; int /*<<< orphan*/  rq_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void svc_xprt_copy_addrs(struct svc_rqst *rqstp, struct svc_xprt *xprt)
{
	struct sockaddr *sin;

	memcpy(&rqstp->rq_addr, &xprt->xpt_remote, xprt->xpt_remotelen);
	rqstp->rq_addrlen = xprt->xpt_remotelen;

	/*
	 * Destination address in request is needed for binding the
	 * source address in RPC replies/callbacks later.
	 */
	sin = (struct sockaddr *)&xprt->xpt_local;
	switch (sin->sa_family) {
	case AF_INET:
		rqstp->rq_daddr.addr = ((struct sockaddr_in *)sin)->sin_addr;
		break;
	case AF_INET6:
		rqstp->rq_daddr.addr6 = ((struct sockaddr_in6 *)sin)->sin6_addr;
		break;
	}
}