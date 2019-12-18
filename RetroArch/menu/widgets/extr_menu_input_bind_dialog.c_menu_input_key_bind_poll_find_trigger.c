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
struct retro_keybind {int dummy; } ;
struct menu_bind_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_ACTION_MAX_USERS ; 
 unsigned int* input_driver_get_uint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_input_key_bind_poll_find_trigger_pad (struct menu_bind_state*,struct menu_bind_state*,struct retro_keybind*,unsigned int) ; 

__attribute__((used)) static bool menu_input_key_bind_poll_find_trigger(
      struct menu_bind_state *state,
      struct menu_bind_state *new_state,
      struct retro_keybind * output
   )
{
   unsigned i;
   unsigned max_users   = *(input_driver_get_uint(INPUT_ACTION_MAX_USERS));

   if (!state || !new_state)
      return false;

   for (i = 0; i < max_users; i++)
   {
      if (!menu_input_key_bind_poll_find_trigger_pad( state, new_state, output, i))
        continue;

      return true;
   }

   return false;
}