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
union svc_addr_u {int /*<<< orphan*/  addr6; int /*<<< orphan*/  addr; } ;
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int sin_family; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

__attribute__((used)) static void rpc_svcaddr2sockaddr(struct sockaddr *sa, unsigned short family, union svc_addr_u *svcaddr)
{
	switch (family) {
	case AF_INET:
		((struct sockaddr_in *)sa)->sin_family = AF_INET;
		((struct sockaddr_in *)sa)->sin_addr = svcaddr->addr;
		return;
	case AF_INET6:
		((struct sockaddr_in6 *)sa)->sin6_family = AF_INET6;
		((struct sockaddr_in6 *)sa)->sin6_addr = svcaddr->addr6;
		return;
	}
}