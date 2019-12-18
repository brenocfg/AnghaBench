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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_lock_init () ; 
 int /*<<< orphan*/  clock_oldconfig () ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntp_init () ; 
 int /*<<< orphan*/  settime_lock ; 
 int /*<<< orphan*/  settime_lock_attr ; 
 int /*<<< orphan*/  settime_lock_grp ; 
 int /*<<< orphan*/  settime_lock_grp_attr ; 
 int /*<<< orphan*/  ticks_per_sec ; 

void
clock_config(void)
{

	clock_lock_init();

	settime_lock_grp_attr = lck_grp_attr_alloc_init();
	settime_lock_grp = lck_grp_alloc_init("settime grp", settime_lock_grp_attr);
	settime_lock_attr = lck_attr_alloc_init();
	lck_mtx_init(&settime_lock, settime_lock_grp, settime_lock_attr);

	clock_oldconfig();

	ntp_init();

	nanoseconds_to_absolutetime((uint64_t)NSEC_PER_SEC, &ticks_per_sec);
}