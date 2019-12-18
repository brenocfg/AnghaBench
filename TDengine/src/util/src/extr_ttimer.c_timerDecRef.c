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
struct TYPE_4__ {int /*<<< orphan*/  refCount; } ;
typedef  TYPE_1__ tmr_obj_t ;

/* Variables and functions */
 scalar_t__ atomic_sub_fetch_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void timerDecRef(tmr_obj_t* timer) {
  if (atomic_sub_fetch_8(&timer->refCount, 1) == 0) {
    free(timer);
  }
}