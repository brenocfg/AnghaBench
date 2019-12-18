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
 int /*<<< orphan*/  acct_subsys_lck_grp ; 
 int /*<<< orphan*/  acct_subsys_mutex ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
acct_init(void)
{
	acct_subsys_lck_grp = lck_grp_alloc_init("acct", NULL);
	acct_subsys_mutex = lck_mtx_alloc_init(acct_subsys_lck_grp, NULL);
}