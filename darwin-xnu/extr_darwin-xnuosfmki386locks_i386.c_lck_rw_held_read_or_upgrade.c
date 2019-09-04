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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LCK_RW_INTERLOCK ; 
 int LCK_RW_SHARED_MASK ; 
 int LCK_RW_WANT_UPGRADE ; 
 int /*<<< orphan*/  TRUE ; 
 int ordered_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline boolean_t
lck_rw_held_read_or_upgrade(lck_rw_t *lock)
{
	if (ordered_load(&lock->data) & (LCK_RW_SHARED_MASK | LCK_RW_INTERLOCK | LCK_RW_WANT_UPGRADE))
		return TRUE;
	return FALSE;
}