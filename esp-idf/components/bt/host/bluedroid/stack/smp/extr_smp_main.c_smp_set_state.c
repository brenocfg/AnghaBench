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
typedef  scalar_t__ tSMP_STATE ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ SMP_STATE_MAX ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,scalar_t__,...) ; 
 TYPE_1__ smp_cb ; 
 int /*<<< orphan*/  smp_get_state_name (scalar_t__) ; 

void smp_set_state(tSMP_STATE state)
{
    if (state < SMP_STATE_MAX) {
        SMP_TRACE_DEBUG( "State change: %s(%d) ==> %s(%d)",
                         smp_get_state_name(smp_cb.state), smp_cb.state,
                         smp_get_state_name(state), state );
        smp_cb.state = state;
    } else {
        SMP_TRACE_DEBUG("smp_set_state invalid state =%d", state );
    }
}