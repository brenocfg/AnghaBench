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
 scalar_t__ memcmp (void*,void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int __atomic_compare_exchange_c(int size, void *ptr, void *expected,
                                void *desired, int success, int failure) {
#define LOCK_FREE_ACTION(type)                                                 \
  return __c11_atomic_compare_exchange_strong(                                 \
      (_Atomic(type) *)ptr, (type *)expected, *(type *)desired, success,       \
      failure)
  LOCK_FREE_CASES();
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(ptr);
  lock(l);
  if (memcmp(ptr, expected, size) == 0) {
    memcpy(ptr, desired, size);
    unlock(l);
    return 1;
  }
  memcpy(expected, ptr, size);
  unlock(l);
  return 0;
}