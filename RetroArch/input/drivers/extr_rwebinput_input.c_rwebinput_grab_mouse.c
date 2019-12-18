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
 int /*<<< orphan*/  EM_TRUE ; 
 int /*<<< orphan*/  emscripten_exit_pointerlock () ; 
 int /*<<< orphan*/  emscripten_request_pointerlock (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rwebinput_grab_mouse(void *data, bool state)
{
   (void)data;

   if (state)
      emscripten_request_pointerlock("#canvas", EM_TRUE);
   else
      emscripten_exit_pointerlock();
}