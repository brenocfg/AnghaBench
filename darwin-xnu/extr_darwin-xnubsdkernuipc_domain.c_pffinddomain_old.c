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
struct domain_old {int dummy; } ;
struct domain {int dom_flags; struct domain_old* dom_old; } ;
typedef  int /*<<< orphan*/  domain_guard_t ;

/* Variables and functions */
 int DOM_OLD ; 
 int /*<<< orphan*/  domain_guard_deploy () ; 
 int /*<<< orphan*/  domain_guard_release (int /*<<< orphan*/ ) ; 
 struct domain* pffinddomain_locked (int) ; 

struct domain_old *
pffinddomain_old(int pf)
{
	struct domain_old *odp = NULL;
	struct domain *dp;
	domain_guard_t guard;

	guard = domain_guard_deploy();
	if ((dp = pffinddomain_locked(pf)) != NULL && (dp->dom_flags & DOM_OLD))
		odp = dp->dom_old;
	domain_guard_release(guard);
	return (odp);
}