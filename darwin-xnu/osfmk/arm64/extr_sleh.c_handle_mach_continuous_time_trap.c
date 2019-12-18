#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_2__ {int /*<<< orphan*/ * x; } ;

/* Variables and functions */
 int /*<<< orphan*/  mach_continuous_time () ; 
 TYPE_1__* saved_state64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_mach_continuous_time_trap(arm_saved_state_t *state)
{
	uint64_t now = mach_continuous_time();
	saved_state64(state)->x[0] = now;
}