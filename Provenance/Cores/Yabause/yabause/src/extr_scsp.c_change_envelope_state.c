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
struct TYPE_2__ {int envelope; scalar_t__ step_count; } ;
struct Slot {TYPE_1__ state; } ;
typedef  enum EnvelopeStates { ____Placeholder_EnvelopeStates } EnvelopeStates ;

/* Variables and functions */

void change_envelope_state(struct Slot * slot, enum EnvelopeStates new_state)
{
   slot->state.envelope = new_state;
   slot->state.step_count = 0;
}