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
struct TYPE_3__ {scalar_t__ lock_mtx_cnt; scalar_t__ lock_mtx_util_cnt; scalar_t__ lockgroup_name; int /*<<< orphan*/  lock_mtx_wait_cnt; int /*<<< orphan*/  lock_mtx_miss_cnt; int /*<<< orphan*/  lock_mtx_held_cnt; } ;
typedef  TYPE_1__ lockgroup_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 

void
print_mutex(int requested, lockgroup_info_t *lockgroup)
{
	lockgroup_info_t	*curptr = &lockgroup[requested];

	if (curptr->lock_mtx_cnt != 0 && curptr->lock_mtx_util_cnt != 0) {
		printf("%16lld ", curptr->lock_mtx_util_cnt);
#if defined(__i386__) || defined(__x86_64__)
		printf("%10lld %10lld %10lld   ", curptr->lock_mtx_miss_cnt,  curptr->lock_mtx_wait_cnt, curptr->lock_mtx_held_cnt);
#else
		printf("%16lld %16lld   ", curptr->lock_mtx_miss_cnt,  curptr->lock_mtx_wait_cnt);
#endif
		printf("%-14s\n", curptr->lockgroup_name);
	}
}