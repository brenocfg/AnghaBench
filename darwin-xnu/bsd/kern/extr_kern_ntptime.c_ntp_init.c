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
 int /*<<< orphan*/  L_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_ntp_loop () ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_spin_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntp_lock ; 
 int /*<<< orphan*/  ntp_lock_attr ; 
 int /*<<< orphan*/  ntp_lock_grp ; 
 int /*<<< orphan*/  ntp_lock_grp_attr ; 
 int /*<<< orphan*/  time_freq ; 
 int /*<<< orphan*/  time_offset ; 
 scalar_t__ updated ; 

void
ntp_init(void)
{

	L_CLR(time_offset);
	L_CLR(time_freq);

	ntp_lock_grp_attr = lck_grp_attr_alloc_init();
	ntp_lock_grp =  lck_grp_alloc_init("ntp_lock", ntp_lock_grp_attr);
	ntp_lock_attr = lck_attr_alloc_init();
	ntp_lock = lck_spin_alloc_init(ntp_lock_grp, ntp_lock_attr);

	updated = 0;

	init_ntp_loop();
}