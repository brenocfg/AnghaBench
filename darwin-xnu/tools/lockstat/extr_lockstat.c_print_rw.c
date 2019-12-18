#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lock_rw_cnt; scalar_t__ lock_rw_util_cnt; scalar_t__ lockgroup_name; int /*<<< orphan*/  lock_rw_wait_cnt; int /*<<< orphan*/  lock_rw_miss_cnt; } ;
typedef  TYPE_1__ lockgroup_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 

void
print_rw(int requested, lockgroup_info_t *lockgroup)
{
	lockgroup_info_t	*curptr = &lockgroup[requested];

	if (curptr->lock_rw_cnt != 0 && curptr->lock_rw_util_cnt != 0) {
		printf("%16lld ", curptr->lock_rw_util_cnt);
		printf("%16lld %16lld   ", curptr->lock_rw_miss_cnt,  curptr->lock_rw_wait_cnt);
		printf("%-14s\n", curptr->lockgroup_name);
	}
}