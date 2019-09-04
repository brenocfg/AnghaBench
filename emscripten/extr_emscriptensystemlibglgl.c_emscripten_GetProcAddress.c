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
 void* emscripten_webgl1_get_proc_address (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* strstr (char*,char*) ; 

void* emscripten_GetProcAddress(const char *name_) {
  char *name = malloc(strlen(name_)+1);
  strcpy(name, name_);
  // remove EXT|ARB|OES|ANGLE suffixes
  char *end = strstr(name, "EXT");
  if (end) *end = 0;
  end = strstr(name, "ARB");
  if (end) *end = 0;
  end = strstr(name, "OES");
  if (end) *end = 0;
  end = strstr(name, "ANGLE");
  if (end) *end = 0;

  void *ptr = emscripten_webgl1_get_proc_address(name);

#if LEGACY_GL_EMULATION
  if (!ptr) ptr = emscripten_legacy_gl_emulation_GetProcAddress(name);
#endif
#if USE_WEBGL2
  if (!ptr) ptr = emscripten_webgl2_get_proc_address(name);
#endif

  free(name);
  return ptr;
}