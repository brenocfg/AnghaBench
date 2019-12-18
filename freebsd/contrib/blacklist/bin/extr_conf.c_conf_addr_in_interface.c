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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct ifaddrs {int ifa_flags; TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int IFF_UP ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char* SIF_NAME (struct sockaddr_storage const*) ; 
 int conf_inet_eq (TYPE_1__*,struct sockaddr_storage const*,int) ; 
 struct ifaddrs* ifas ; 
 int /*<<< orphan*/  lfun (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int
conf_addr_in_interface(const struct sockaddr_storage *s1,
    const struct sockaddr_storage *s2, int mask)
{
	const char *name = SIF_NAME(s2);
	const struct ifaddrs *ifa;

	for (ifa = ifas; ifa; ifa = ifa->ifa_next) {
		if ((ifa->ifa_flags & IFF_UP) == 0)
			continue;

		if (strcmp(ifa->ifa_name, name) != 0)
			continue;

		if (s1->ss_family != ifa->ifa_addr->sa_family)
			continue;

		bool eq;
		switch (s1->ss_family) {
		case AF_INET:
		case AF_INET6:
			eq = conf_inet_eq(ifa->ifa_addr, s1, mask);
			break;
		default:
			(*lfun)(LOG_ERR, "Bad family %u", s1->ss_family);
			continue;
		}
		if (eq)
			return 1;
	}
	return 0;
}