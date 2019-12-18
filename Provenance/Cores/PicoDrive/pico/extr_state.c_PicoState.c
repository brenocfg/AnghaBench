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
 int /*<<< orphan*/  areaClose (void*) ; 
 void* open_save_file (char const*,int) ; 
 int pico_state_internal (void*,int) ; 

int PicoState(const char *fname, int is_save)
{
  void *afile = NULL;
  int ret;

  afile = open_save_file(fname, is_save);
  if (afile == NULL)
    return -1;

  ret = pico_state_internal(afile, is_save);
  areaClose(afile);
  return ret;
}