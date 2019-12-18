#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ endian; } ;

/* Variables and functions */
 scalar_t__ ENDIAN_BIG ; 
 scalar_t__ ENDIAN_LITTLE ; 
 TYPE_1__ command_line ; 
 char const* output_target ; 

void
lang_add_output_format (const char *format,
			const char *big,
			const char *little,
			int from_script)
{
  if (output_target == NULL || !from_script)
    {
      if (command_line.endian == ENDIAN_BIG
	  && big != NULL)
	format = big;
      else if (command_line.endian == ENDIAN_LITTLE
	       && little != NULL)
	format = little;

      output_target = format;
    }
}