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
 scalar_t__ DEBUG_STABS ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,...) ; 
 char bfd_get_symbol_leading_char (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  stabs_generate_asm_endfunc (char*,char*) ; 
 int /*<<< orphan*/  stabs_generate_asm_func (char*,char*) ; 
 int /*<<< orphan*/  stdoutput ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
do_s_func (int end_p, const char *default_prefix)
{
  /* Record the current function so that we can issue an error message for
     misplaced .func,.endfunc, and also so that .endfunc needs no
     arguments.  */
  static char *current_name;
  static char *current_label;

  if (end_p)
    {
      if (current_name == NULL)
	{
	  as_bad (_("missing .func"));
	  ignore_rest_of_line ();
	  return;
	}

      if (debug_type == DEBUG_STABS)
	stabs_generate_asm_endfunc (current_name, current_label);

      current_name = current_label = NULL;
    }
  else /* ! end_p */
    {
      char *name, *label;
      char delim1, delim2;

      if (current_name != NULL)
	{
	  as_bad (_(".endfunc missing for previous .func"));
	  ignore_rest_of_line ();
	  return;
	}

      name = input_line_pointer;
      delim1 = get_symbol_end ();
      name = xstrdup (name);
      *input_line_pointer = delim1;
      SKIP_WHITESPACE ();
      if (*input_line_pointer != ',')
	{
	  if (default_prefix)
	    asprintf (&label, "%s%s", default_prefix, name);
	  else
	    {
	      char leading_char = bfd_get_symbol_leading_char (stdoutput);
	      /* Missing entry point, use function's name with the leading
		 char prepended.  */
	      if (leading_char)
		asprintf (&label, "%c%s", leading_char, name);
	      else
		label = name;
	    }
	}
      else
	{
	  ++input_line_pointer;
	  SKIP_WHITESPACE ();
	  label = input_line_pointer;
	  delim2 = get_symbol_end ();
	  label = xstrdup (label);
	  *input_line_pointer = delim2;
	}

      if (debug_type == DEBUG_STABS)
	stabs_generate_asm_func (name, label);

      current_name = name;
      current_label = label;
    }

  demand_empty_rest_of_line ();
}