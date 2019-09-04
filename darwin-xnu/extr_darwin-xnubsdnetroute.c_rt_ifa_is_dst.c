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
struct sockaddr {scalar_t__ sa_family; } ;
struct ifaddr {struct sockaddr* ifa_addr; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {scalar_t__ s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 scalar_t__ SA6_ARE_ADDR_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SIN (struct sockaddr*) ; 
 int /*<<< orphan*/  SIN6 (struct sockaddr*) ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
rt_ifa_is_dst(struct sockaddr *dst, struct ifaddr *ifa)
{
	boolean_t result = FALSE;

	if (ifa == NULL || ifa->ifa_addr == NULL)
		return (result);

	IFA_LOCK_SPIN(ifa);

	if (dst->sa_family == ifa->ifa_addr->sa_family &&
	    ((dst->sa_family == AF_INET &&
	    SIN(dst)->sin_addr.s_addr ==
	    SIN(ifa->ifa_addr)->sin_addr.s_addr) ||
	    (dst->sa_family == AF_INET6 &&
	    SA6_ARE_ADDR_EQUAL(SIN6(dst), SIN6(ifa->ifa_addr)))))
		result = TRUE;

	IFA_UNLOCK(ifa);

	return (result);
}