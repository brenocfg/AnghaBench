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
struct policy {int* addr; size_t len; int mask; } ;
struct in6_addr {int* s6_addr; } ;

/* Variables and functions */
 struct policy const* defpolicy ; 
 scalar_t__ memcmp (int*,int*,size_t) ; 

__attribute__((used)) static const struct policy *policyof(const struct in6_addr *a)
{
	int i;
	for (i=0; ; i++) {
		if (memcmp(a->s6_addr, defpolicy[i].addr, defpolicy[i].len))
			continue;
		if ((a->s6_addr[defpolicy[i].len] & defpolicy[i].mask)
		    != defpolicy[i].addr[defpolicy[i].len])
			continue;
		return defpolicy+i;
	}
}