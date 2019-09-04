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
 int /*<<< orphan*/  EM_ASM (int) ; 
 int /*<<< orphan*/  EM_CALLBACK_THREAD_CONTEXT_CALLING_THREAD ; 
 int /*<<< orphan*/  EM_CALLBACK_THREAD_CONTEXT_MAIN_BROWSER_THREAD ; 
 int* Module ; 
 void* application_main_thread_id ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* emscripten_main_browser_thread_id () ; 
 int /*<<< orphan*/  emscripten_set_keydown_callback_on_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_keypress_callback_on_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_keyup_callback_on_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keydown_callback_on_main_browser_thread ; 
 int /*<<< orphan*/  keypress_callback_on_application_main_thread ; 
 int /*<<< orphan*/  keyup_callback_on_application_main_thread ; 
 void* main_browser_thread_id ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_self () ; 

int main()
{
  main_browser_thread_id = emscripten_main_browser_thread_id();
  assert(main_browser_thread_id);
  application_main_thread_id = (void*)pthread_self();
  assert(application_main_thread_id);

  printf("Main browser thread ID: %p, application main thread ID: %p\n", main_browser_thread_id, application_main_thread_id);

  emscripten_set_keydown_callback_on_thread(0, 0, 1, keydown_callback_on_main_browser_thread, EM_CALLBACK_THREAD_CONTEXT_MAIN_BROWSER_THREAD);
  emscripten_set_keypress_callback_on_thread(0, 0, 1, keypress_callback_on_application_main_thread, EM_CALLBACK_THREAD_CONTEXT_CALLING_THREAD);
  emscripten_set_keyup_callback_on_thread(0, 0, 1, keyup_callback_on_application_main_thread, EM_CALLBACK_THREAD_CONTEXT_CALLING_THREAD);

  printf("Please press the Enter key.\n");

  EM_ASM(Module['noExitRuntime'] = true);
}