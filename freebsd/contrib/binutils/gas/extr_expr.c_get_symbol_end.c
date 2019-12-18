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
 scalar_t__* input_line_pointer ; 
 scalar_t__ is_name_beginner (char) ; 
 scalar_t__ is_name_ender (char) ; 
 scalar_t__ is_part_of_name (char) ; 

char
get_symbol_end (void)
{
  char c;

  /* We accept \001 in a name in case this is being called with a
     constructed string.  */
  if (is_name_beginner (c = *input_line_pointer++) || c == '\001')
    {
      while (is_part_of_name (c = *input_line_pointer++)
	     || c == '\001')
	;
      if (is_name_ender (c))
	c = *input_line_pointer++;
    }
  *--input_line_pointer = 0;
  return (c);
}