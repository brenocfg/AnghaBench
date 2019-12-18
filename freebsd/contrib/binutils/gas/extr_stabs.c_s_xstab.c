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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  s_stab_generic (int,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

void
s_xstab (int what)
{
  int length;
  char *stab_secname, *stabstr_secname;
  static char *saved_secname, *saved_strsecname;

  /* @@ MEMORY LEAK: This allocates a copy of the string, but in most
     cases it will be the same string, so we could release the storage
     back to the obstack it came from.  */
  stab_secname = demand_copy_C_string (&length);
  SKIP_WHITESPACE ();
  if (*input_line_pointer == ',')
    input_line_pointer++;
  else
    {
      as_bad (_("comma missing in .xstabs"));
      ignore_rest_of_line ();
      return;
    }

  /* To get the name of the stab string section, simply add "str" to
     the stab section name.  */
  if (saved_secname == 0 || strcmp (saved_secname, stab_secname))
    {
      stabstr_secname = (char *) xmalloc (strlen (stab_secname) + 4);
      strcpy (stabstr_secname, stab_secname);
      strcat (stabstr_secname, "str");
      if (saved_secname)
	{
	  free (saved_secname);
	  free (saved_strsecname);
	}
      saved_secname = stab_secname;
      saved_strsecname = stabstr_secname;
    }
  s_stab_generic (what, saved_secname, saved_strsecname);
}