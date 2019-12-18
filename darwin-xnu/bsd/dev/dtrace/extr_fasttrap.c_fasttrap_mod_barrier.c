#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpuc_pid_lock; } ;

/* Variables and functions */
 unsigned int NCPU ; 
 TYPE_1__* cpu_core ; 
 scalar_t__ fasttrap_mod_gen ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_mod_barrier(uint64_t gen)
{
	unsigned int i;

	if (gen < fasttrap_mod_gen)
		return;

	fasttrap_mod_gen++;

	for (i = 0; i < NCPU; i++) {
		lck_mtx_lock(&cpu_core[i].cpuc_pid_lock);
		lck_mtx_unlock(&cpu_core[i].cpuc_pid_lock);
	}
}