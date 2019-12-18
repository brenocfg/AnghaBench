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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ atomic_val_compare_exchange_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  taosGetPthreadId () ; 

__attribute__((used)) static void lockTimerList(timer_list_t* list) {
  int64_t tid = taosGetPthreadId();
  int       i = 0;
  while (atomic_val_compare_exchange_64(&(list->lockedBy), 0, tid) != 0) {
    if (++i % 1000 == 0) {
      sched_yield();
    }
  }
}