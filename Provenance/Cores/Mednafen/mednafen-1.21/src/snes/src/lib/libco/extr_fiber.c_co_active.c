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
typedef  scalar_t__ cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertThreadToFiber (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentFiber () ; 
 scalar_t__ co_active_ ; 

cothread_t co_active() {
  if(!co_active_) {
    ConvertThreadToFiber(0);
    co_active_ = GetCurrentFiber();
  }
  return co_active_;
}