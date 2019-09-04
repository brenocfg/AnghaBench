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
 void* emscripten_webgl1_get_proc_address (char const*) ; 

extern void *emscripten_webgl_get_proc_address(const char *name)
{
  void *ptr = emscripten_webgl1_get_proc_address(name);
#if USE_WEBGL2
  if (!ptr) ptr = emscripten_webgl2_get_proc_address(name);
#endif
  return ptr;
}