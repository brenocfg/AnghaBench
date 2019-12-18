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
struct TYPE_4__ {scalar_t__* s6_addr32; } ;
struct sockaddr_in6 {int sin6_len; TYPE_2__ sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ IPV6_ADDR_INT32_SMP ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 

void
in6_sin_2_v4mapsin6(struct sockaddr_in *sin, struct sockaddr_in6 *sin6)
{
	bzero(sin6, sizeof (*sin6));
	sin6->sin6_len = sizeof (struct sockaddr_in6);
	sin6->sin6_family = AF_INET6;
	sin6->sin6_port = sin->sin_port;
	sin6->sin6_addr.s6_addr32[0] = 0;
	sin6->sin6_addr.s6_addr32[1] = 0;
	if (sin->sin_addr.s_addr) {
		sin6->sin6_addr.s6_addr32[2] = IPV6_ADDR_INT32_SMP;
		sin6->sin6_addr.s6_addr32[3] = sin->sin_addr.s_addr;
	} else {
		sin6->sin6_addr.s6_addr32[2] = 0;
		sin6->sin6_addr.s6_addr32[3] = 0;
	}
}