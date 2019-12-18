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
struct domain {int dummy; } ;
typedef  int /*<<< orphan*/  domain_guard_t ;

/* Variables and functions */
 int /*<<< orphan*/  domain_guard_deploy () ; 
 int /*<<< orphan*/  domain_guard_release (int /*<<< orphan*/ ) ; 
 struct domain* pffinddomain_locked (int) ; 

struct domain *
pffinddomain(int pf)
{
	struct domain *dp;
	domain_guard_t guard;

	guard = domain_guard_deploy();
	dp = pffinddomain_locked(pf);
	domain_guard_release(guard);
	return (dp);
}