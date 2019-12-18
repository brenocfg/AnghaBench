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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct nfs_server {TYPE_1__* nfs_client; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_compare_super_address(struct nfs_server *server1,
				     struct nfs_server *server2)
{
	struct sockaddr *sap1, *sap2;

	sap1 = (struct sockaddr *)&server1->nfs_client->cl_addr;
	sap2 = (struct sockaddr *)&server2->nfs_client->cl_addr;

	if (sap1->sa_family != sap2->sa_family)
		return 0;

	switch (sap1->sa_family) {
	case AF_INET: {
		struct sockaddr_in *sin1 = (struct sockaddr_in *)sap1;
		struct sockaddr_in *sin2 = (struct sockaddr_in *)sap2;
		if (sin1->sin_addr.s_addr != sin2->sin_addr.s_addr)
			return 0;
		if (sin1->sin_port != sin2->sin_port)
			return 0;
		break;
	}
	case AF_INET6: {
		struct sockaddr_in6 *sin1 = (struct sockaddr_in6 *)sap1;
		struct sockaddr_in6 *sin2 = (struct sockaddr_in6 *)sap2;
		if (!ipv6_addr_equal(&sin1->sin6_addr, &sin2->sin6_addr))
			return 0;
		if (sin1->sin6_port != sin2->sin6_port)
			return 0;
		break;
	}
	default:
		return 0;
	}

	return 1;
}