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
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 struct dlm_ctxt* __dlm_lookup_domain_full (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static struct dlm_ctxt * __dlm_lookup_domain(const char *domain)
{
	assert_spin_locked(&dlm_domain_lock);

	return __dlm_lookup_domain_full(domain, strlen(domain));
}