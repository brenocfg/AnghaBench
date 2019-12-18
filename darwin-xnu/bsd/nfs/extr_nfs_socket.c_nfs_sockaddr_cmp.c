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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; scalar_t__ sa_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
nfs_sockaddr_cmp(struct sockaddr *sa1, struct sockaddr *sa2)
{
	if (!sa1)
		return (-1);
	if (!sa2)
		return (1);
	if (sa1->sa_family != sa2->sa_family)
		return ((sa1->sa_family < sa2->sa_family) ? -1 : 1);
	if (sa1->sa_len != sa2->sa_len)
		return ((sa1->sa_len < sa2->sa_len) ? -1 : 1);
	if (sa1->sa_family == AF_INET)
		return (bcmp(&((struct sockaddr_in*)sa1)->sin_addr,
			     &((struct sockaddr_in*)sa2)->sin_addr, sizeof(((struct sockaddr_in*)sa1)->sin_addr)));
	if (sa1->sa_family == AF_INET6)
		return (bcmp(&((struct sockaddr_in6*)sa1)->sin6_addr,
			     &((struct sockaddr_in6*)sa2)->sin6_addr, sizeof(((struct sockaddr_in6*)sa1)->sin6_addr)));
	return (-1);
}