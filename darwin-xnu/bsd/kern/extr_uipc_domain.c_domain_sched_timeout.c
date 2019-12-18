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

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ TRUE ; 
 scalar_t__ domain_draining ; 
 int /*<<< orphan*/  domain_timeout ; 
 int /*<<< orphan*/  domain_timeout_mtx ; 
 scalar_t__ domain_timeout_run ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
domain_sched_timeout(void)
{
	LCK_MTX_ASSERT(&domain_timeout_mtx, LCK_MTX_ASSERT_OWNED);

	if (!domain_timeout_run && domain_draining) {
		domain_timeout_run = TRUE;
		timeout(domain_timeout, NULL, hz);
	}
}