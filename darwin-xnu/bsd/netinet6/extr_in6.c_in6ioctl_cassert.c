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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
#define  SIOCAADDRCTL_POLICY 133 
#define  SIOCDADDRCTL_POLICY 132 
#define  SIOCDRADD_IN6_32 131 
#define  SIOCDRADD_IN6_64 130 
#define  SIOCDRDEL_IN6_32 129 
#define  SIOCDRDEL_IN6_64 128 

__attribute__((used)) static __attribute__((unused)) void
in6ioctl_cassert(void)
{
	/*
	 * This is equivalent to _CASSERT() and the compiler wouldn't
	 * generate any instructions, thus for compile time only.
	 */
	switch ((u_long)0) {
	case 0:

	/* bsd/netinet6/in6_var.h */
	case SIOCAADDRCTL_POLICY:
	case SIOCDADDRCTL_POLICY:
	case SIOCDRADD_IN6_32:
	case SIOCDRADD_IN6_64:
	case SIOCDRDEL_IN6_32:
	case SIOCDRDEL_IN6_64:
		;
	}
}