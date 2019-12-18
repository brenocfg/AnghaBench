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
typedef  union sctp_addr {int dummy; } sctp_addr ;
typedef  scalar_t__ sctp_scope_t ;

/* Variables and functions */
 scalar_t__ SCTP_SCOPE_LINK ; 
#define  SCTP_SCOPE_POLICY_DISABLE 131 
#define  SCTP_SCOPE_POLICY_ENABLE 130 
#define  SCTP_SCOPE_POLICY_LINK 129 
#define  SCTP_SCOPE_POLICY_PRIVATE 128 
 scalar_t__ SCTP_SCOPE_PRIVATE ; 
 scalar_t__ SCTP_SCOPE_UNUSABLE ; 
 scalar_t__ sctp_scope (union sctp_addr const*) ; 
 int sctp_scope_policy ; 

int sctp_in_scope(const union sctp_addr *addr, sctp_scope_t scope)
{
	sctp_scope_t addr_scope = sctp_scope(addr);

	/* The unusable SCTP addresses will not be considered with
	 * any defined scopes.
	 */
	if (SCTP_SCOPE_UNUSABLE == addr_scope)
		return 0;
	/*
	 * For INIT and INIT-ACK address list, let L be the level of
	 * of requested destination address, sender and receiver
	 * SHOULD include all of its addresses with level greater
	 * than or equal to L.
	 *
	 * Address scoping can be selectively controlled via sysctl
	 * option
	 */
	switch (sctp_scope_policy) {
	case SCTP_SCOPE_POLICY_DISABLE:
		return 1;
	case SCTP_SCOPE_POLICY_ENABLE:
		if (addr_scope <= scope)
			return 1;
		break;
	case SCTP_SCOPE_POLICY_PRIVATE:
		if (addr_scope <= scope || SCTP_SCOPE_PRIVATE == addr_scope)
			return 1;
		break;
	case SCTP_SCOPE_POLICY_LINK:
		if (addr_scope <= scope || SCTP_SCOPE_LINK == addr_scope)
			return 1;
		break;
	default:
		break;
	}

	return 0;
}