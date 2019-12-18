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
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/ * is_end_of_line ; 

__attribute__((used)) static char *
get_mri_string (int terminator, int *len)
{
  char *ret;
  char *s;

  SKIP_WHITESPACE ();
  s = ret = input_line_pointer;
  if (*input_line_pointer == '\'')
    {
      ++s;
      ++input_line_pointer;
      while (! is_end_of_line[(unsigned char) *input_line_pointer])
	{
	  *s++ = *input_line_pointer++;
	  if (s[-1] == '\'')
	    {
	      if (*input_line_pointer != '\'')
		break;
	      ++input_line_pointer;
	    }
	}
      SKIP_WHITESPACE ();
    }
  else
    {
      while (*input_line_pointer != terminator
	     && ! is_end_of_line[(unsigned char) *input_line_pointer])
	++input_line_pointer;
      s = input_line_pointer;
      while (s > ret && (s[-1] == ' ' || s[-1] == '\t'))
	--s;
    }

  *len = s - ret;
  return ret;
}