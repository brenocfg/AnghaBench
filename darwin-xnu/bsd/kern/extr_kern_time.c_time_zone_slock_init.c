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
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_spin_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tz_slock ; 
 int /*<<< orphan*/  tz_slock_attr ; 
 int /*<<< orphan*/  tz_slock_grp ; 
 int /*<<< orphan*/  tz_slock_grp_attr ; 

void
time_zone_slock_init(void)
{
	/* allocate lock group attribute and group */
	tz_slock_grp_attr = lck_grp_attr_alloc_init();

	tz_slock_grp =  lck_grp_alloc_init("tzlock", tz_slock_grp_attr);

	/* Allocate lock attribute */
	tz_slock_attr = lck_attr_alloc_init();

	/* Allocate the spin lock */
	tz_slock = lck_spin_alloc_init(tz_slock_grp, tz_slock_attr);
}