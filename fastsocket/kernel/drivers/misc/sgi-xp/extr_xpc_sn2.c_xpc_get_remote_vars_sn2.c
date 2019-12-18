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
struct xpc_vars_sn2 {int /*<<< orphan*/  version; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int /*<<< orphan*/  XPC_RP_VARS_SIZE ; 
 scalar_t__ XPC_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPC_V_VERSION ; 
 int xpBadVersion ; 
 int xpSuccess ; 
 int xpVarsNotSet ; 
 int /*<<< orphan*/  xp_pa (struct xpc_vars_sn2*) ; 
 int xp_remote_memcpy (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum xp_retval
xpc_get_remote_vars_sn2(unsigned long remote_vars_pa,
			struct xpc_vars_sn2 *remote_vars)
{
	enum xp_retval ret;

	if (remote_vars_pa == 0)
		return xpVarsNotSet;

	/* pull over the cross partition variables */
	ret = xp_remote_memcpy(xp_pa(remote_vars), remote_vars_pa,
			       XPC_RP_VARS_SIZE);
	if (ret != xpSuccess)
		return ret;

	if (XPC_VERSION_MAJOR(remote_vars->version) !=
	    XPC_VERSION_MAJOR(XPC_V_VERSION)) {
		return xpBadVersion;
	}

	return xpSuccess;
}