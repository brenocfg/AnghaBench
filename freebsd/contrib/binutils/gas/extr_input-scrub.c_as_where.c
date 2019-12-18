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
 char* logical_input_file ; 
 unsigned int logical_input_line ; 
 char* physical_input_file ; 
 unsigned int physical_input_line ; 

void
as_where (char **namep, unsigned int *linep)
{
  if (logical_input_file != NULL
      && (linep == NULL || logical_input_line >= 0))
    {
      *namep = logical_input_file;
      if (linep != NULL)
	*linep = logical_input_line;
    }
  else if (physical_input_file != NULL)
    {
      *namep = physical_input_file;
      if (linep != NULL)
	*linep = physical_input_line;
    }
  else
    {
      *namep = 0;
      if (linep != NULL)
	*linep = 0;
    }
}