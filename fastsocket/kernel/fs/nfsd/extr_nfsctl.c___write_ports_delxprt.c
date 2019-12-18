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
struct svc_xprt {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTCONN ; 
 int USHORT_MAX ; 
 int /*<<< orphan*/ * nfsd_serv ; 
 int sscanf (char*,char*,char*,int*) ; 
 int /*<<< orphan*/  svc_close_xprt (struct svc_xprt*) ; 
 struct svc_xprt* svc_find_xprt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svc_xprt_put (struct svc_xprt*) ; 

__attribute__((used)) static ssize_t __write_ports_delxprt(char *buf)
{
	struct svc_xprt *xprt;
	char transport[16];
	int port;

	if (sscanf(&buf[1], "%15s %4u", transport, &port) != 2)
		return -EINVAL;

	if (port < 1 || port > USHORT_MAX || nfsd_serv == NULL)
		return -EINVAL;

	xprt = svc_find_xprt(nfsd_serv, transport, AF_UNSPEC, port);
	if (xprt == NULL)
		return -ENOTCONN;

	svc_close_xprt(xprt);
	svc_xprt_put(xprt);
	return 0;
}