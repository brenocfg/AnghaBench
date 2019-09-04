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
struct domain {int dom_flags; } ;

/* Variables and functions */
 int DOM_ATTACHED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dom_entry ; 
 int /*<<< orphan*/  domain_proto_mtx_lock_assert_held () ; 
 int /*<<< orphan*/  domains ; 

__attribute__((used)) static void
attach_domain(struct domain *dp)
{
	domain_proto_mtx_lock_assert_held();
	VERIFY(!(dp->dom_flags & DOM_ATTACHED));

	TAILQ_INSERT_TAIL(&domains, dp, dom_entry);
	dp->dom_flags |= DOM_ATTACHED;
}