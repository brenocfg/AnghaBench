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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct sock_xprt {int /*<<< orphan*/  xprt; int /*<<< orphan*/  sock; } ;
typedef  int /*<<< orphan*/  any ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int kernel_connect (int /*<<< orphan*/ ,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xs_sock_reset_connection_flags (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xs_abort_connection(struct sock_xprt *transport)
{
	int result;
	struct sockaddr any;

	dprintk("RPC:       disconnecting xprt %p to reuse port\n", transport);

	/*
	 * Disconnect the transport socket by doing a connect operation
	 * with AF_UNSPEC.  This should return immediately...
	 */
	memset(&any, 0, sizeof(any));
	any.sa_family = AF_UNSPEC;
	result = kernel_connect(transport->sock, &any, sizeof(any), 0);
	if (!result)
		xs_sock_reset_connection_flags(&transport->xprt);
	dprintk("RPC:       AF_UNSPEC connect return code %d\n", result);
}