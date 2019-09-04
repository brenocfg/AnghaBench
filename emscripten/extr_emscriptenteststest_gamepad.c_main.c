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
typedef  int /*<<< orphan*/  EMSCRIPTEN_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  TEST_RESULT (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  emscripten_set_gamepadconnected_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_gamepaddisconnected_callback (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gamepad_callback ; 
 int /*<<< orphan*/  mainloop ; 

int main()
{
  EMSCRIPTEN_RESULT ret = emscripten_set_gamepadconnected_callback(0, 1, gamepad_callback);
  TEST_RESULT(emscripten_set_gamepadconnected_callback);
  ret = emscripten_set_gamepaddisconnected_callback(0, 1, gamepad_callback);
  TEST_RESULT(emscripten_set_gamepaddisconnected_callback);

  emscripten_set_main_loop(mainloop, 10, 0);

  /* For the events to function, one must either call emscripten_set_main_loop or enable Module.noExitRuntime by some other means. 
     Otherwise the application will exit after leaving main(), and the atexit handlers will clean up all event hooks (by design). */
  EM_ASM(Module['noExitRuntime'] = true);

#ifdef REPORT_RESULT
  // Keep the page running for a moment.
  emscripten_async_call(report_result, 0, 5000);
#endif
  return 0;
}