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
struct dm_region_hash {int /*<<< orphan*/  context; int /*<<< orphan*/  (* wakeup_all_recovery_waiters ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  recovery_in_flight; int /*<<< orphan*/  recovery_count; } ;

/* Variables and functions */
 scalar_t__ __rh_recovery_prepare (struct dm_region_hash*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void dm_rh_recovery_prepare(struct dm_region_hash *rh)
{
	/* Extra reference to avoid race with dm_rh_stop_recovery */
	atomic_inc(&rh->recovery_in_flight);

	while (!down_trylock(&rh->recovery_count)) {
		atomic_inc(&rh->recovery_in_flight);
		if (__rh_recovery_prepare(rh) <= 0) {
			atomic_dec(&rh->recovery_in_flight);
			up(&rh->recovery_count);
			break;
		}
	}

	/* Drop the extra reference */
	if (atomic_dec_and_test(&rh->recovery_in_flight))
		rh->wakeup_all_recovery_waiters(rh->context);
}