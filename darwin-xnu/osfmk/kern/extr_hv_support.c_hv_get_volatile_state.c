#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ hv_volatile_state_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ids; } ;
struct TYPE_4__ {TYPE_1__ machine; } ;

/* Variables and functions */
 scalar_t__ HV_DEBUG_STATE ; 
 TYPE_2__* current_thread () ; 

int
hv_get_volatile_state(hv_volatile_state_t state) {
	int is_volatile = 0;

#if (defined(__x86_64__))
	if (state == HV_DEBUG_STATE) {
		is_volatile = (current_thread()->machine.ids != NULL);
	}
#endif

	return is_volatile;
}