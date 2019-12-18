#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_bits_t ;
struct TYPE_3__ {unsigned int numButtons; scalar_t__* digitalButton; } ;
typedef  TYPE_1__ EmscriptenGamepadEvent ;
typedef  scalar_t__ EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT256_SET_PTR (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 scalar_t__ emscripten_get_gamepad_status (unsigned int,TYPE_1__*) ; 

__attribute__((used)) static void rwebpad_joypad_get_buttons(unsigned port_num, input_bits_t *state)
{
   EmscriptenGamepadEvent gamepad_state;
   EMSCRIPTEN_RESULT r = emscripten_get_gamepad_status(
         port_num, &gamepad_state);

   if (r == EMSCRIPTEN_RESULT_SUCCESS)
   {
      unsigned i;

      for (i = 0; i < gamepad_state.numButtons; i++)
      {
         if (gamepad_state.digitalButton[i])
            BIT256_SET_PTR(state, i);
      }
   }
   else
      BIT256_CLEAR_ALL_PTR(state);
}