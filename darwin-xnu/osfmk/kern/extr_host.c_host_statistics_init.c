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
 int HOST_STATISTICS_TIME_WINDOW ; 
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  host_statistics_lck ; 
 int /*<<< orphan*/  host_statistics_lck_grp ; 
 int /*<<< orphan*/  host_statistics_time_window ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (int,int /*<<< orphan*/ *) ; 

void
host_statistics_init(void)
{
	host_statistics_lck_grp = lck_grp_alloc_init("host_statistics", LCK_GRP_ATTR_NULL);
	lck_mtx_init(&host_statistics_lck, host_statistics_lck_grp, LCK_ATTR_NULL);
	nanoseconds_to_absolutetime((HOST_STATISTICS_TIME_WINDOW * NSEC_PER_SEC), &host_statistics_time_window);
}