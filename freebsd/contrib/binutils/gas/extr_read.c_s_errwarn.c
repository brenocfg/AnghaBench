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
 char* _ (char*) ; 
 int /*<<< orphan*/  as_bad (char*,char*) ; 
 int /*<<< orphan*/  as_warn (char*,char*) ; 
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  is_it_end_of_statement () ; 

void
s_errwarn (int err)
{
  int len;
  /* The purpose for the conditional assignment is not to
     internationalize the directive itself, but that we need a
     self-contained message, one that can be passed like the
     demand_copy_C_string return value, and with no assumption on the
     location of the name of the directive within the message.  */
  char *msg
    = (err ? _(".error directive invoked in source file")
       : _(".warning directive invoked in source file"));

  if (!is_it_end_of_statement ())
    {
      if (*input_line_pointer != '\"')
	{
	  as_bad (_("%s argument must be a string"),
		  err ? ".error" : ".warning");
	  ignore_rest_of_line ();
	  return;
	}

      msg = demand_copy_C_string (&len);
      if (msg == NULL)
	return;
    }

  if (err)
    as_bad ("%s", msg);
  else
    as_warn ("%s", msg);
  demand_empty_rest_of_line ();
}