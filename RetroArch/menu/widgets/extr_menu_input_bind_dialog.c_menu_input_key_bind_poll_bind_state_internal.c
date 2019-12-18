#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct menu_bind_state {TYPE_1__* state; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* poll ) () ;} ;
typedef  TYPE_2__ input_device_driver_t ;
struct TYPE_7__ {int /*<<< orphan*/ * hats; int /*<<< orphan*/ * axes; int /*<<< orphan*/ * buttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAT_DOWN_MASK ; 
 int /*<<< orphan*/  HAT_LEFT_MASK ; 
 int /*<<< orphan*/  HAT_RIGHT_MASK ; 
 int /*<<< orphan*/  HAT_UP_MASK ; 
 unsigned int MENU_MAX_AXES ; 
 unsigned int MENU_MAX_BUTTONS ; 
 unsigned int MENU_MAX_HATS ; 
 int /*<<< orphan*/  input_joypad_axis_raw (TYPE_2__ const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  input_joypad_button_raw (TYPE_2__ const*,unsigned int,unsigned int) ; 
 scalar_t__ input_joypad_hat_raw (TYPE_2__ const*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void menu_input_key_bind_poll_bind_state_internal(
      const input_device_driver_t *joypad,
      struct menu_bind_state *state,
      unsigned port,
      bool timed_out)
{
   unsigned b, a, h;
    if (!joypad)
        return;

    if (joypad->poll)
        joypad->poll();

    /* poll only the relevant port */
    for (b = 0; b < MENU_MAX_BUTTONS; b++)
        state->state[port].buttons[b] =
           input_joypad_button_raw(joypad, port, b);

    for (a = 0; a < MENU_MAX_AXES; a++)
        state->state[port].axes[a] =
           input_joypad_axis_raw(joypad, port, a);

    for (h = 0; h < MENU_MAX_HATS; h++)
    {
        if (input_joypad_hat_raw(joypad, port, HAT_UP_MASK, h))
            state->state[port].hats[h] |= HAT_UP_MASK;
        if (input_joypad_hat_raw(joypad, port, HAT_DOWN_MASK, h))
            state->state[port].hats[h] |= HAT_DOWN_MASK;
        if (input_joypad_hat_raw(joypad, port, HAT_LEFT_MASK, h))
            state->state[port].hats[h] |= HAT_LEFT_MASK;
        if (input_joypad_hat_raw(joypad, port, HAT_RIGHT_MASK, h))
            state->state[port].hats[h] |= HAT_RIGHT_MASK;
    }
}