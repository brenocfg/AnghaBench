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
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int nfs_sockaddr_cmp_ip4 (struct sockaddr const*,struct sockaddr const*) ; 
 int nfs_sockaddr_cmp_ip6 (struct sockaddr const*,struct sockaddr const*) ; 

__attribute__((used)) static int nfs_sockaddr_cmp(const struct sockaddr *sa1,
			    const struct sockaddr *sa2)
{
	if (sa1->sa_family != sa2->sa_family)
		return 0;

	switch (sa1->sa_family) {
	case AF_INET:
		return nfs_sockaddr_cmp_ip4(sa1, sa2);
	case AF_INET6:
		return nfs_sockaddr_cmp_ip6(sa1, sa2);
	}
	return 0;
}