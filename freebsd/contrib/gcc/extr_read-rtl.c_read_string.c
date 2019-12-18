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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_expected_char (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  fatal_with_file_and_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 char* read_braced_string (int /*<<< orphan*/ *) ; 
 char* read_quoted_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rtx_filename ; 
 int read_rtx_lineno ; 
 int read_skip_spaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rtx_ptr_loc (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_obstack ; 

__attribute__((used)) static char *
read_string (FILE *infile, int star_if_braced)
{
  char *stringbuf;
  int saw_paren = 0;
  int c, old_lineno;

  c = read_skip_spaces (infile);
  if (c == '(')
    {
      saw_paren = 1;
      c = read_skip_spaces (infile);
    }

  old_lineno = read_rtx_lineno;
  if (c == '"')
    stringbuf = read_quoted_string (infile);
  else if (c == '{')
    {
      if (star_if_braced)
	obstack_1grow (&string_obstack, '*');
      stringbuf = read_braced_string (infile);
    }
  else
    fatal_with_file_and_line (infile, "expected `\"' or `{', found `%c'", c);

  if (saw_paren)
    {
      c = read_skip_spaces (infile);
      if (c != ')')
	fatal_expected_char (infile, ')', c);
    }

  set_rtx_ptr_loc (stringbuf, read_rtx_filename, old_lineno);
  return stringbuf;
}