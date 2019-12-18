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
 scalar_t__ TRUE ; 
 scalar_t__ had_output_filename ; 
 char const* output_filename ; 

void
lang_add_output (const char *name, int from_script)
{
  /* Make -o on command line override OUTPUT in script.  */
  if (!had_output_filename || !from_script)
    {
      output_filename = name;
      had_output_filename = TRUE;
    }
}