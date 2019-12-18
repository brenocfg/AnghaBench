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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ lck_rw_t ;

/* Variables and functions */
 int LCK_RW_INTERLOCK ; 
 int /*<<< orphan*/  cpu_pause () ; 
 int ordered_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
lck_rw_interlock_spin(lck_rw_t *lock)
{
	while (ordered_load(&lock->data) & LCK_RW_INTERLOCK) {
		cpu_pause();
	}
}