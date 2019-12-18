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
 int /*<<< orphan*/  abort () ; 
 char* logical_input_file ; 
 int logical_input_line ; 
 char* physical_input_file ; 
 int physical_input_line ; 
 scalar_t__ strcmp (char*,char*) ; 

int
new_logical_line_flags (char *fname, /* DON'T destroy it!  We point to it!  */
			int line_number,
			int flags)
{
  switch (flags)
    {
    case 0:
      break;
    case 1:
      if (line_number != -1)
	abort ();
      break;
    case 1 << 1:
    case 1 << 2:
      /* FIXME: we could check that include nesting is correct.  */
      break;
    default:
      abort ();
    }

  if (line_number >= 0)
    logical_input_line = line_number;
  else if (line_number == -1 && fname && !*fname && (flags & (1 << 2)))
    {
      logical_input_file = physical_input_file;
      logical_input_line = physical_input_line;
      fname = NULL;
    }

  if (fname
      && (logical_input_file == NULL
	  || strcmp (logical_input_file, fname)))
    {
      logical_input_file = fname;
      return 1;
    }
  else
    return 0;
}