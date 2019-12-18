#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  lck_rw_data; } ;
typedef  TYPE_1__ lck_rw_t ;

/* Variables and functions */
 int LCK_RW_INTERLOCK ; 
 int /*<<< orphan*/  clear_exclusive () ; 
 int load_exclusive32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_event () ; 

__attribute__((used)) static inline void
lck_rw_interlock_spin(lck_rw_t *lock)
{
#if __SMP__
	uint32_t	data;

	for ( ; ; ) {
		data = load_exclusive32(&lock->lck_rw_data, memory_order_relaxed);
		if (data & LCK_RW_INTERLOCK)
			wait_for_event();
		else {
			clear_exclusive();
			return;
		}
	}
#else
	panic("lck_rw_interlock_spin(): Interlock locked %p %x", lock, lock->lck_rw_data);
#endif
}