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
 int /*<<< orphan*/  N_FUN ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*,int /*<<< orphan*/ ,unsigned int,char const*) ; 
 int /*<<< orphan*/  current_function_label ; 
 int /*<<< orphan*/  free (char*) ; 
 int in_dot_func_p ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  s_stab (char) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
stabs_generate_asm_func (const char *funcname, const char *startlabname)
{
  static int void_emitted_p;
  char *hold = input_line_pointer;
  char *buf;
  char *file;
  unsigned int lineno;

  if (! void_emitted_p)
    {
      input_line_pointer = "\"void:t1=1\",128,0,0,0";
      s_stab ('s');
      void_emitted_p = 1;
    }

  as_where (&file, &lineno);
  asprintf (&buf, "\"%s:F1\",%d,0,%d,%s",
	    funcname, N_FUN, lineno + 1, startlabname);
  input_line_pointer = buf;
  s_stab ('s');
  free (buf);

  input_line_pointer = hold;
  current_function_label = xstrdup (startlabname);
  in_dot_func_p = 1;
}