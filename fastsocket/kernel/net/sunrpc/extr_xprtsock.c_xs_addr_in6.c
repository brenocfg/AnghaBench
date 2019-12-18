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
struct sockaddr_in6 {int dummy; } ;
struct rpc_xprt {int /*<<< orphan*/  addr; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sockaddr_in6 *xs_addr_in6(struct rpc_xprt *xprt)
{
	return (struct sockaddr_in6 *) &xprt->addr;
}