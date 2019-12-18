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
struct os_reason {int dummy; } ;

/* Variables and functions */
 int OS_REASON_MAX_COUNT ; 
 int /*<<< orphan*/  OS_REASON_RESERVE_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  os_reason_lock_attr ; 
 int /*<<< orphan*/  os_reason_lock_grp ; 
 int /*<<< orphan*/  os_reason_lock_grp_attr ; 
 int /*<<< orphan*/ * os_reason_zone ; 
 int /*<<< orphan*/  panic (char*) ; 
 int zfill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zinit (int,int,int,char*) ; 

void
os_reason_init()
{
	int reasons_allocated = 0;

	/*
	 * Initialize OS reason group and lock attributes
	 */
	os_reason_lock_grp_attr =  lck_grp_attr_alloc_init();
	os_reason_lock_grp = lck_grp_alloc_init("os_reason_lock", os_reason_lock_grp_attr);
	os_reason_lock_attr = lck_attr_alloc_init();

	/*
	 * Create OS reason zone.
	 */
	os_reason_zone = zinit(sizeof(struct os_reason), OS_REASON_MAX_COUNT * sizeof(struct os_reason),
				OS_REASON_MAX_COUNT, "os reasons");
	if (os_reason_zone == NULL) {
		panic("failed to initialize os_reason_zone");
	}

	/*
	 * We pre-fill the OS reason zone to reduce the likelihood that
	 * the jetsam thread and others block when they create an exit
	 * reason. This pre-filled memory is not-collectable since it's
	 * foreign memory crammed in as part of zfill().
	 */
	reasons_allocated = zfill(os_reason_zone, OS_REASON_RESERVE_COUNT);
	assert(reasons_allocated > 0);
}