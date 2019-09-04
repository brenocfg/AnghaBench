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
struct TYPE_3__ {int /*<<< orphan*/  lck_rw_interlock; } ;
typedef  TYPE_1__ lck_rw_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  hw_lock_byte_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lck_interlock_unlock(lck_rw_t *lck, boolean_t istate)
{               
	hw_lock_byte_unlock(&lck->lck_rw_interlock);
	ml_set_interrupts_enabled(istate);
}