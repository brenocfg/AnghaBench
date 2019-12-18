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
typedef  int /*<<< orphan*/  Lock ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_FREE_CASES () ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lock_for_pointer (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void __atomic_exchange_c(int size, void *ptr, void *val, void *old, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  *(type *)old =                                                               \
      __c11_atomic_exchange((_Atomic(type) *)ptr, *(type *)val, model);        \
  return;
  LOCK_FREE_CASES();
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  memcpy(old, ptr, size);
  memcpy(ptr, val, size);
  unlock(l);
}