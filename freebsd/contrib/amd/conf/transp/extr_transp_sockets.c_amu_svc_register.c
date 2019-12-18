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
typedef  int /*<<< orphan*/  u_long ;
struct netconfig {int dummy; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int svc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct svc_req*,int /*<<< orphan*/ *),int /*<<< orphan*/ ) ; 

int
amu_svc_register(SVCXPRT *xprt, u_long prognum, u_long versnum,
		 void (*dispatch)(struct svc_req *rqstp, SVCXPRT *transp),
		 u_long protocol, struct netconfig *dummy)
{
  /* on Sockets: svc_register returns 1 on success, 0 otherwise */
  return svc_register(xprt, prognum, versnum, dispatch, protocol);
}