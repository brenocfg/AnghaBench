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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 scalar_t__ is_a_char (unsigned int) ; 
 unsigned int next_char_of_string () ; 
 int /*<<< orphan*/  notes ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 char* obstack_finish (int /*<<< orphan*/ *) ; 

char *
demand_copy_string (int *lenP)
{
  register unsigned int c;
  register int len;
  char *retval;

  len = 0;
  SKIP_WHITESPACE ();
  if (*input_line_pointer == '\"')
    {
      input_line_pointer++;	/* Skip opening quote.  */

      while (is_a_char (c = next_char_of_string ()))
	{
	  obstack_1grow (&notes, c);
	  len++;
	}
      /* JF this next line is so demand_copy_C_string will return a
	 null terminated string.  */
      obstack_1grow (&notes, '\0');
      retval = obstack_finish (&notes);
    }
  else
    {
      as_bad (_("missing string"));
      retval = NULL;
      ignore_rest_of_line ();
    }
  *lenP = len;
  return (retval);
}