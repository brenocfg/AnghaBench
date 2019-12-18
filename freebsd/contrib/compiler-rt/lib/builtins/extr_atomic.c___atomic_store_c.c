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

void __atomic_store_c(int size, void *dest, void *src, int model) {
#define LOCK_FREE_ACTION(type)                                                 \
  __c11_atomic_store((_Atomic(type) *)dest, *(type *)src, model);              \
  return;
  LOCK_FREE_CASES();
#undef LOCK_FREE_ACTION
  Lock *l = lock_for_pointer(dest);
  lock(l);
  memcpy(dest, src, size);
  unlock(l);
}