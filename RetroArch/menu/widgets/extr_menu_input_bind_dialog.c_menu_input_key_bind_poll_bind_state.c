#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct menu_bind_state {int skip; TYPE_4__* state; } ;
struct TYPE_6__ {float axis_threshold; int /*<<< orphan*/ * auto_binds; scalar_t__ joy_idx; } ;
typedef  TYPE_1__ rarch_joypad_info_t ;
struct TYPE_7__ {scalar_t__ (* input_state ) (void*,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ input_driver_t ;
typedef  int /*<<< orphan*/  input_device_driver_t ;
struct TYPE_8__ {int /*<<< orphan*/ * mbuttons; } ;

/* Variables and functions */
 unsigned int MENU_MAX_MBUTTONS ; 
 int /*<<< orphan*/  RETROK_RETURN ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/ * input_driver_get_joypad_driver () ; 
 int /*<<< orphan*/ * input_driver_get_sec_joypad_driver () ; 
 void* input_get_data () ; 
 TYPE_2__* input_get_ptr () ; 
 int /*<<< orphan*/  input_mouse_button_raw (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_input_key_bind_poll_bind_state_internal (int /*<<< orphan*/  const*,struct menu_bind_state*,unsigned int,int) ; 
 scalar_t__ stub1 (void*,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_input_key_bind_poll_bind_state(
      struct menu_bind_state *state,
      unsigned port,
      bool timed_out)
{
   unsigned b;
   rarch_joypad_info_t joypad_info;
   input_driver_t *input_ptr               = input_get_ptr();
   void *input_data                        = input_get_data();
   const input_device_driver_t *joypad     =
      input_driver_get_joypad_driver();
   const input_device_driver_t *sec_joypad =
      input_driver_get_sec_joypad_driver();

   if (!state)
      return;

   memset(state->state, 0, sizeof(state->state));

    /* poll mouse (on the relevant port) */
    for (b = 0; b < MENU_MAX_MBUTTONS; b++)
        state->state[port].mbuttons[b] =
           input_mouse_button_raw(port, b);

   joypad_info.joy_idx        = 0;
   joypad_info.auto_binds     = NULL;
   joypad_info.axis_threshold = 0.0f;

   state->skip = timed_out || input_ptr->input_state(input_data,
         joypad_info,
         NULL,
         0, RETRO_DEVICE_KEYBOARD, 0, RETROK_RETURN);

   menu_input_key_bind_poll_bind_state_internal(
         joypad, state, port, timed_out);

   if (sec_joypad)
      menu_input_key_bind_poll_bind_state_internal(
            sec_joypad, state, port, timed_out);
}