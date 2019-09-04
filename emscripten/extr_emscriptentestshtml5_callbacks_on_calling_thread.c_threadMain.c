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
 int /*<<< orphan*/  EMSCRIPTEN_EVENT_TARGET_WINDOW ; 
 scalar_t__ EMSCRIPTEN_RESULT_SUCCESS ; 
 int /*<<< orphan*/  EM_ASM (int) ; 
 int* Module ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ emscripten_set_mousemove_callback (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_callback ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  registeringThreadId ; 

void *threadMain(void *arg)
{
  registeringThreadId = pthread_self();

  EMSCRIPTEN_RESULT ret = emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, (void*)0x42, 1, mouse_callback);
  assert(ret == EMSCRIPTEN_RESULT_SUCCESS);

  printf("Please move the mouse cursor.\n");

#ifdef TEST_SYNC_BLOCKING_LOOP
  for(;;)
  {
    usleep(1000);
    emscripten_current_thread_process_queued_calls();
  }
#else
  EM_ASM(Module['noExitRuntime'] = true);
#endif
  return 0;
}