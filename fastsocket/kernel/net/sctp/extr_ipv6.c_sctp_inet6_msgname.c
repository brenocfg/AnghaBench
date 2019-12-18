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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 

__attribute__((used)) static void sctp_inet6_msgname(char *msgname, int *addr_len)
{
	struct sockaddr_in6 *sin6;

	sin6 = (struct sockaddr_in6 *)msgname;
	sin6->sin6_family = AF_INET6;
	sin6->sin6_flowinfo = 0;
	sin6->sin6_scope_id = 0; /*FIXME */
	*addr_len = sizeof(struct sockaddr_in6);
}