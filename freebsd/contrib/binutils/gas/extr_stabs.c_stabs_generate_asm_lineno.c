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
 char* FAKE_LABEL_NAME ; 
 int N_SLINE ; 
 int /*<<< orphan*/  N_SOL ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  colon (char*) ; 
 char* current_function_label ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  generate_asm_file (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ in_dot_func_p ; 
 char* input_line_pointer ; 
 int outputting_stabs_line_debug ; 
 int /*<<< orphan*/  s_stab (char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* xstrdup (char*) ; 

void
stabs_generate_asm_lineno (void)
{
  static int label_count;
  char *hold;
  char *file;
  unsigned int lineno;
  char *buf;
  char sym[30];
  /* Remember the last file/line and avoid duplicates.  */
  static unsigned int prev_lineno = -1;
  static char *prev_file = NULL;

  /* Rather than try to do this in some efficient fashion, we just
     generate a string and then parse it again.  That lets us use the
     existing stabs hook, which expect to see a string, rather than
     inventing new ones.  */

  hold = input_line_pointer;

  as_where (&file, &lineno);

  /* Don't emit sequences of stabs for the same line.  */
  if (prev_file == NULL)
    {
      /* First time thru.  */
      prev_file = xstrdup (file);
      prev_lineno = lineno;
    }
  else if (lineno == prev_lineno
	   && strcmp (file, prev_file) == 0)
    {
      /* Same file/line as last time.  */
      return;
    }
  else
    {
      /* Remember file/line for next time.  */
      prev_lineno = lineno;
      if (strcmp (file, prev_file) != 0)
	{
	  free (prev_file);
	  prev_file = xstrdup (file);
	}
    }

  /* Let the world know that we are in the middle of generating a
     piece of stabs line debugging information.  */
  outputting_stabs_line_debug = 1;

  generate_asm_file (N_SOL, file);

  sprintf (sym, "%sL%d", FAKE_LABEL_NAME, label_count);
  ++label_count;

  if (in_dot_func_p)
    {
      buf = (char *) alloca (100 + strlen (current_function_label));
      sprintf (buf, "%d,0,%d,%s-%s\n", N_SLINE, lineno,
	       sym, current_function_label);
    }
  else
    {
      buf = (char *) alloca (100);
      sprintf (buf, "%d,0,%d,%s\n", N_SLINE, lineno, sym);
    }
  input_line_pointer = buf;
  s_stab ('n');
  colon (sym);

  input_line_pointer = hold;
  outputting_stabs_line_debug = 0;
}