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
typedef  scalar_t__ EMSCRIPTEN_RESULT ;

/* Variables and functions */
 scalar_t__ EMSCRIPTEN_RESULT_NOT_SUPPORTED ; 
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  RARCH_ERR (char*,scalar_t__) ; 
 scalar_t__ emscripten_sample_gamepad_data () ; 
 scalar_t__ emscripten_set_gamepadconnected_callback (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ emscripten_set_gamepaddisconnected_callback (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int g_rwebpad_initialized ; 
 int /*<<< orphan*/  rwebpad_gamepad_cb ; 

__attribute__((used)) static bool rwebpad_joypad_init(void *data)
{
   EMSCRIPTEN_RESULT supported;
   (void)data;

   supported = emscripten_sample_gamepad_data();
   if (supported == EMSCRIPTEN_RESULT_NOT_SUPPORTED)
      return false;

   if (!g_rwebpad_initialized)
   {
      EMSCRIPTEN_RESULT r;
      g_rwebpad_initialized = true;

      /* callbacks needs to be registered for gamepads to connect */
      r = emscripten_set_gamepadconnected_callback(NULL, false,
         rwebpad_gamepad_cb);
      if (r != EMSCRIPTEN_RESULT_SUCCESS)
      {
         RARCH_ERR(
            "[EMSCRIPTEN/PAD] failed to create connect callback: %d\n", r);
      }

      r = emscripten_set_gamepaddisconnected_callback(NULL, false,
         rwebpad_gamepad_cb);
      if (r != EMSCRIPTEN_RESULT_SUCCESS)
      {
         RARCH_ERR(
            "[EMSCRIPTEN/PAD] failed to create disconnect callback: %d\n", r);
      }
   }

   return true;
}