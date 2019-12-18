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
struct type {int dummy; } ;
struct format_data {char format; int count; scalar_t__ size; } ;
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_CODE_VOID ; 
 scalar_t__ VALUE_TYPE (struct value*) ; 
 struct value* access_value_history (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_value_begin (scalar_t__) ; 
 int /*<<< orphan*/  annotate_value_end () ; 
 int /*<<< orphan*/  annotate_value_history_begin (int,scalar_t__) ; 
 int /*<<< orphan*/  annotate_value_history_end () ; 
 int /*<<< orphan*/  annotate_value_history_value () ; 
 struct format_data decode_format (char**,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int inspect_it ; 
 char last_format ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  print_formatted (struct value*,char,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int record_latest_value (struct value*) ; 
 int /*<<< orphan*/  validate_format (struct format_data,char*) ; 

__attribute__((used)) static void
print_command_1 (char *exp, int inspect, int voidprint)
{
  struct expression *expr;
  struct cleanup *old_chain = 0;
  char format = 0;
  struct value *val;
  struct format_data fmt;
  int cleanup = 0;

  /* Pass inspect flag to the rest of the print routines in a global (sigh). */
  inspect_it = inspect;

  if (exp && *exp == '/')
    {
      exp++;
      fmt = decode_format (&exp, last_format, 0);
      validate_format (fmt, "print");
      last_format = format = fmt.format;
    }
  else
    {
      fmt.count = 1;
      fmt.format = 0;
      fmt.size = 0;
    }

  if (exp && *exp)
    {
      struct type *type;
      expr = parse_expression (exp);
      old_chain = make_cleanup (free_current_contents, &expr);
      cleanup = 1;
      val = evaluate_expression (expr);
    }
  else
    val = access_value_history (0);

  if (voidprint || (val && VALUE_TYPE (val) &&
		    TYPE_CODE (VALUE_TYPE (val)) != TYPE_CODE_VOID))
    {
      int histindex = record_latest_value (val);

      if (histindex >= 0)
	annotate_value_history_begin (histindex, VALUE_TYPE (val));
      else
	annotate_value_begin (VALUE_TYPE (val));

      if (inspect)
	printf_unfiltered ("\031(gdb-makebuffer \"%s\"  %d '(\"", exp, histindex);
      else if (histindex >= 0)
	printf_filtered ("$%d = ", histindex);

      if (histindex >= 0)
	annotate_value_history_value ();

      print_formatted (val, format, fmt.size, gdb_stdout);
      printf_filtered ("\n");

      if (histindex >= 0)
	annotate_value_history_end ();
      else
	annotate_value_end ();

      if (inspect)
	printf_unfiltered ("\") )\030");
    }

  if (cleanup)
    do_cleanups (old_chain);
  inspect_it = 0;		/* Reset print routines to normal */
}