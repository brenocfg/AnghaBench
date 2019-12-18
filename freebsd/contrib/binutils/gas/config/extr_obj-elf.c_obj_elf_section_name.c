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
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ strchr (char*,char) ; 
 char* tc_canonicalize_section_name (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static char *
obj_elf_section_name (void)
{
  char *name;

  SKIP_WHITESPACE ();
  if (*input_line_pointer == '"')
    {
      int dummy;

      name = demand_copy_C_string (&dummy);
      if (name == NULL)
	{
	  ignore_rest_of_line ();
	  return NULL;
	}
    }
  else
    {
      char *end = input_line_pointer;

      while (0 == strchr ("\n\t,; ", *end))
	end++;
      if (end == input_line_pointer)
	{
	  as_bad (_("missing name"));
	  ignore_rest_of_line ();
	  return NULL;
	}

      name = xmalloc (end - input_line_pointer + 1);
      memcpy (name, input_line_pointer, end - input_line_pointer);
      name[end - input_line_pointer] = '\0';
#ifdef tc_canonicalize_section_name
      name = tc_canonicalize_section_name (name);
#endif
      input_line_pointer = end;
    }
  SKIP_WHITESPACE ();
  return name;
}