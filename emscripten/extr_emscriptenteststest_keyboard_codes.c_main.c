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

/* Variables and functions */
 int /*<<< orphan*/  EMSCRIPTEN_EVENT_TARGET_WINDOW ; 
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  emscripten_set_keydown_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_keypress_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_keyup_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
  printf("Press any keys on the keyboard to test the appropriate generated EmscriptenKeyboardEvent structure.\n");
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
  emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
  EM_ASM(Module['noExitRuntime'] = true);
}