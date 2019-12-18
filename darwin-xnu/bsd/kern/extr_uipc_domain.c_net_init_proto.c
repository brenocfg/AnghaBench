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
struct protosw {int pr_flags; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int PR_ATTACHED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  domain_proto_mtx_lock_assert_held () ; 
 int /*<<< orphan*/  init_proto (struct protosw*,struct domain*) ; 

void
net_init_proto(struct protosw *pp, struct domain *dp)
{
	/*
	 * This could be called as part of initializing the domain,
	 * and thus DOM_INITIALIZED may not be set (yet).  The protocol
	 * must have been attached via net_addr_protosw() by now.
	 */
	domain_proto_mtx_lock_assert_held();
	VERIFY(pp->pr_flags & PR_ATTACHED);

	init_proto(pp, dp);
}