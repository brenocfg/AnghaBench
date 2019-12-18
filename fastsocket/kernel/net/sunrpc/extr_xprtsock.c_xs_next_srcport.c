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
struct TYPE_2__ {int /*<<< orphan*/  resvport; } ;
struct sock_xprt {scalar_t__ srcport; TYPE_1__ xprt; } ;

/* Variables and functions */
 unsigned short xprt_max_resvport ; 
 unsigned short xprt_min_resvport ; 

__attribute__((used)) static unsigned short xs_next_srcport(struct sock_xprt *transport, unsigned short port)
{
	if (transport->srcport != 0)
		transport->srcport = 0;
	if (!transport->xprt.resvport)
		return 0;
	if (port <= xprt_min_resvport || port > xprt_max_resvport)
		return xprt_max_resvport;
	return --port;
}