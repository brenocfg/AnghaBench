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
union corpse_creation_gate {int /*<<< orphan*/  value; int /*<<< orphan*/  corpses; int /*<<< orphan*/  user_faults; } ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int CORPSE_CRASHINFO_HAS_REF ; 
 int CORPSE_CRASHINFO_USER_FAULT ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TOTAL_CORPSES_ALLOWED ; 
 scalar_t__ TOTAL_USER_FAULTS_ALLOWED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_compare_exchange_strong_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflight_corpses ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static kern_return_t
task_crashinfo_get_ref(uint16_t kcd_u_flags)
{
	union corpse_creation_gate oldgate, newgate;

	assert(kcd_u_flags & CORPSE_CRASHINFO_HAS_REF);

	oldgate.value = atomic_load_explicit(&inflight_corpses, memory_order_relaxed);
	for (;;) {
		newgate = oldgate;
		if (kcd_u_flags & CORPSE_CRASHINFO_USER_FAULT) {
			if (newgate.user_faults++ >= TOTAL_USER_FAULTS_ALLOWED) {
				return KERN_RESOURCE_SHORTAGE;
			}
		}
		if (newgate.corpses++ >= TOTAL_CORPSES_ALLOWED) {
			return KERN_RESOURCE_SHORTAGE;
		}

		// this reloads the value in oldgate
		if (atomic_compare_exchange_strong_explicit(&inflight_corpses,
				&oldgate.value, newgate.value, memory_order_relaxed,
				memory_order_relaxed)) {
			return KERN_SUCCESS;
		}
	}
}