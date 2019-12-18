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
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assign_symbol (char*,int) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 char get_symbol_end () ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 

void
s_set (int equiv)
{
  char *name;
  char delim;
  char *end_name;

  /* Especial apologies for the random logic:
     this just grew, and could be parsed much more simply!
     Dean in haste.  */
  name = input_line_pointer;
  delim = get_symbol_end ();
  end_name = input_line_pointer;
  *end_name = delim;

  if (name == end_name)
    {
      as_bad (_("expected symbol name"));
      ignore_rest_of_line ();
      return;
    }

  SKIP_WHITESPACE ();

  if (*input_line_pointer != ',')
    {
      *end_name = 0;
      as_bad (_("expected comma after \"%s\""), name);
      *end_name = delim;
      ignore_rest_of_line ();
      return;
    }

  input_line_pointer++;
  *end_name = 0;

  assign_symbol (name, equiv);
  *end_name = delim;

  demand_empty_rest_of_line ();
}