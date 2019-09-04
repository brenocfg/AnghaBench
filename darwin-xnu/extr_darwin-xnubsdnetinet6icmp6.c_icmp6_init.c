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
struct ip6protosw {int pr_flags; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int PR_ATTACHED ; 
 int PR_INITIALIZED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  mld_init () ; 

void
icmp6_init(struct ip6protosw *pp, struct domain *dp)
{
#pragma unused(dp)
	static int icmp6_initialized = 0;

	/* Also called from ip6_init() without pp */
	VERIFY(pp == NULL ||
	    (pp->pr_flags & (PR_INITIALIZED|PR_ATTACHED)) == PR_ATTACHED);

	/* This gets called by more than one protocols, so initialize once */
	if (!icmp6_initialized) {
		icmp6_initialized = 1;
		mld_init();
	}
}