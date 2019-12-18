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
struct TYPE_3__ {int /*<<< orphan*/  lockedBy; } ;
typedef  TYPE_1__ timer_list_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_val_compare_exchange_64 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ taosGetPthreadId () ; 
 int /*<<< orphan*/  tmrError (char*,scalar_t__) ; 

__attribute__((used)) static void unlockTimerList(timer_list_t* list) {
  int64_t tid = taosGetPthreadId();
  if (atomic_val_compare_exchange_64(&(list->lockedBy), tid, 0) != tid) {
    assert(false);
    tmrError("%d trying to unlock a timer list not locked by current thread.", tid);
  }
}