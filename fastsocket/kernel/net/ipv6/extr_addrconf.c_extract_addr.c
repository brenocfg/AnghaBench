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
struct nlattr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct in6_addr* nla_data (struct nlattr*) ; 
 scalar_t__ nla_memcmp (struct nlattr*,struct in6_addr*,int) ; 

__attribute__((used)) static struct in6_addr *extract_addr(struct nlattr *addr, struct nlattr *local)
{
	struct in6_addr *pfx = NULL;

	if (addr)
		pfx = nla_data(addr);

	if (local) {
		if (pfx && nla_memcmp(local, pfx, sizeof(*pfx)))
			pfx = NULL;
		else
			pfx = nla_data(local);
	}

	return pfx;
}