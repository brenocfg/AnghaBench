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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  domain_draining ; 
 int /*<<< orphan*/  domain_sched_timeout () ; 
 int /*<<< orphan*/  domain_timeout_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
net_drain_domains(void)
{
	lck_mtx_lock(&domain_timeout_mtx);
	domain_draining = TRUE;
	domain_sched_timeout();
	lck_mtx_unlock(&domain_timeout_mtx);
}