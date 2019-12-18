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
typedef  void* u8 ;
struct nlmsghdr {int dummy; } ;
struct ifaddrmsg {int ifa_index; void* ifa_scope; void* ifa_flags; void* ifa_prefixlen; int /*<<< orphan*/  ifa_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 

__attribute__((used)) static void put_ifaddrmsg(struct nlmsghdr *nlh, u8 prefixlen, u8 flags,
			  u8 scope, int ifindex)
{
	struct ifaddrmsg *ifm;

	ifm = nlmsg_data(nlh);
	ifm->ifa_family = AF_INET6;
	ifm->ifa_prefixlen = prefixlen;
	ifm->ifa_flags = flags;
	ifm->ifa_scope = scope;
	ifm->ifa_index = ifindex;
}