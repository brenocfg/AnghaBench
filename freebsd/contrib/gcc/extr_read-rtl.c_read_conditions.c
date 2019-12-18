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
 int /*<<< orphan*/  add_c_test (char*,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fatal_expected_char (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  read_name (char*,int /*<<< orphan*/ *) ; 
 char* read_quoted_string (int /*<<< orphan*/ *) ; 
 int read_skip_spaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_const_int (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
read_conditions (FILE *infile, char *tmp_char)
{
  int c;

  c = read_skip_spaces (infile);
  if (c != '[')
    fatal_expected_char (infile, '[', c);

  while ( (c = read_skip_spaces (infile)) != ']')
    {
      char *expr;
      int value;

      if (c != '(')
	fatal_expected_char (infile, '(', c);

      read_name (tmp_char, infile);
      validate_const_int (infile, tmp_char);
      value = atoi (tmp_char);

      c = read_skip_spaces (infile);
      if (c != '"')
	fatal_expected_char (infile, '"', c);
      expr = read_quoted_string (infile);

      c = read_skip_spaces (infile);
      if (c != ')')
	fatal_expected_char (infile, ')', c);

      add_c_test (expr, value);
    }
  c = read_skip_spaces (infile);
  if (c != ')')
    fatal_expected_char (infile, ')', c);
}