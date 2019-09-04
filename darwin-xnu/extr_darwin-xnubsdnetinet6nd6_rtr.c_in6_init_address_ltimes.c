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
typedef  void* uint64_t ;
struct nd_prefix {int dummy; } ;
struct in6_addrlifetime {scalar_t__ ia6t_vltime; scalar_t__ ia6t_pltime; void* ia6t_preferred; void* ia6t_expire; } ;

/* Variables and functions */
 scalar_t__ ND6_INFINITE_LIFETIME ; 
 void* net_uptime () ; 

__attribute__((used)) static void
in6_init_address_ltimes(struct nd_prefix *new, struct in6_addrlifetime *lt6)
{
#pragma unused(new)
	uint64_t timenow = net_uptime();

	/* Valid lifetime must not be updated unless explicitly specified. */
	/* init ia6t_expire */
	if (lt6->ia6t_vltime == ND6_INFINITE_LIFETIME) {
		lt6->ia6t_expire = 0;
	} else {
		lt6->ia6t_expire = timenow;
		lt6->ia6t_expire += lt6->ia6t_vltime;
	}

	/* init ia6t_preferred */
	if (lt6->ia6t_pltime == ND6_INFINITE_LIFETIME) {
		lt6->ia6t_preferred = 0;
	} else {
		lt6->ia6t_preferred = timenow;
		lt6->ia6t_preferred += lt6->ia6t_pltime;
	}
}