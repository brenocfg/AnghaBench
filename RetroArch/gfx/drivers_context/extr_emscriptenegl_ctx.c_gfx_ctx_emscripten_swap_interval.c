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
 int /*<<< orphan*/  EM_TIMING_RAF ; 
 int /*<<< orphan*/  EM_TIMING_SETIMMEDIATE ; 
 int /*<<< orphan*/  emscripten_set_main_loop_timing (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gfx_ctx_emscripten_swap_interval(void *data, int interval)
{
   (void)data;

   if (interval == 0)
      emscripten_set_main_loop_timing(EM_TIMING_SETIMMEDIATE, 0);
   else
      emscripten_set_main_loop_timing(EM_TIMING_RAF, interval);
}