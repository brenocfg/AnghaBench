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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mac_system_enforce ; 
 int /*<<< orphan*/  system_check_sysctlbyname ; 

int
mac_system_check_sysctlbyname(kauth_cred_t cred, const char *namestring, int *name,
			      u_int namelen, user_addr_t oldctl, size_t oldlen,
			      user_addr_t newctl, size_t newlen)
{
	int error;
	
#if SECURITY_MAC_CHECK_ENFORCE
	/* 21167099 - only check if we allow write */
	if (!mac_system_enforce)
		return (0);
#endif

	MAC_CHECK(system_check_sysctlbyname, cred, namestring,
	    name, namelen, oldctl, oldlen, newctl, newlen);	
	
	return (error);
}