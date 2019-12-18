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
struct value {int dummy; } ;
struct format_data {char format; int /*<<< orphan*/  size; } ;
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  annotate_value_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_value_end () ; 
 struct format_data decode_format (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  print_formatted (struct value*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_format (struct format_data,char*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
output_command (char *exp, int from_tty)
{
  struct expression *expr;
  struct cleanup *old_chain;
  char format = 0;
  struct value *val;
  struct format_data fmt;

  if (exp && *exp == '/')
    {
      exp++;
      fmt = decode_format (&exp, 0, 0);
      validate_format (fmt, "output");
      format = fmt.format;
    }

  expr = parse_expression (exp);
  old_chain = make_cleanup (free_current_contents, &expr);

  val = evaluate_expression (expr);

  annotate_value_begin (VALUE_TYPE (val));

  print_formatted (val, format, fmt.size, gdb_stdout);

  annotate_value_end ();

  wrap_here ("");
  gdb_flush (gdb_stdout);

  do_cleanups (old_chain);
}