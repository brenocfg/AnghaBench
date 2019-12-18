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
 int /*<<< orphan*/  error (char*) ; 
 int get_number (char**) ; 
 int get_number_trailer (char**,char) ; 
 scalar_t__ isspace (int) ; 

int 
get_number_or_range (char **pp)
{
  static int last_retval, end_value;
  static char *end_ptr;
  static int in_range = 0;

  if (**pp != '-')
    {
      /* Default case: pp is pointing either to a solo number, 
	 or to the first number of a range.  */
      last_retval = get_number_trailer (pp, '-');
      if (**pp == '-')
	{
	  char **temp;

	  /* This is the start of a range (<number1> - <number2>).
	     Skip the '-', parse and remember the second number,
	     and also remember the end of the final token.  */

	  temp = &end_ptr; 
	  end_ptr = *pp + 1; 
	  while (isspace ((int) *end_ptr))
	    end_ptr++;	/* skip white space */
	  end_value = get_number (temp);
	  if (end_value < last_retval) 
	    {
	      error ("inverted range");
	    }
	  else if (end_value == last_retval)
	    {
	      /* degenerate range (number1 == number2).  Advance the
		 token pointer so that the range will be treated as a
		 single number.  */ 
	      *pp = end_ptr;
	    }
	  else
	    in_range = 1;
	}
    }
  else if (! in_range)
    error ("negative value");
  else
    {
      /* pp points to the '-' that betokens a range.  All
	 number-parsing has already been done.  Return the next
	 integer value (one greater than the saved previous value).
	 Do not advance the token pointer 'pp' until the end of range
	 is reached.  */

      if (++last_retval == end_value)
	{
	  /* End of range reached; advance token pointer.  */
	  *pp = end_ptr;
	  in_range = 0;
	}
    }
  return last_retval;
}