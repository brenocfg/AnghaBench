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
typedef  int const uint16_t ;
struct TYPE_4__ {int SR; int /*<<< orphan*/  USP; int /*<<< orphan*/ * A; int /*<<< orphan*/  SSP; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int const SR_S ; 
 int /*<<< orphan*/  check_interrupt (TYPE_1__*) ; 

__attribute__((used)) static void set_SR(Q68State *state, uint16_t value)
{
    const uint16_t old_value = state->SR;
    state->SR = value;
    if ((old_value ^ value) & SR_S) {
        if (value & SR_S) {  // Switched to supervisor mode
            state->USP = state->A[7];
            state->A[7] = state->SSP;
        } else {  // Switched to user mode
            state->SSP = state->A[7];
            state->A[7] = state->USP;
        }
    }
    check_interrupt(state);
}