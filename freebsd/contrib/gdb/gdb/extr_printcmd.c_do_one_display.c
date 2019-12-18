#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct TYPE_2__ {int size; int count; char format; } ;
struct display {scalar_t__ enabled_p; int number; TYPE_1__ format; int /*<<< orphan*/  exp; scalar_t__ block; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_BFD_SECTION (struct value*) ; 
 int /*<<< orphan*/  annotate_display_begin () ; 
 int /*<<< orphan*/  annotate_display_end () ; 
 int /*<<< orphan*/  annotate_display_expression () ; 
 int /*<<< orphan*/  annotate_display_expression_end () ; 
 int /*<<< orphan*/  annotate_display_format () ; 
 int /*<<< orphan*/  annotate_display_number_end () ; 
 int /*<<< orphan*/  annotate_display_value () ; 
 int contained_in (int /*<<< orphan*/ ,scalar_t__) ; 
 int current_display_number ; 
 int /*<<< orphan*/  do_examine (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* evaluate_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_formatted (struct value*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  value_as_address (struct value*) ; 

__attribute__((used)) static void
do_one_display (struct display *d)
{
  int within_current_scope;

  if (d->enabled_p == 0)
    return;

  if (d->block)
    within_current_scope = contained_in (get_selected_block (0), d->block);
  else
    within_current_scope = 1;
  if (!within_current_scope)
    return;

  current_display_number = d->number;

  annotate_display_begin ();
  printf_filtered ("%d", d->number);
  annotate_display_number_end ();
  printf_filtered (": ");
  if (d->format.size)
    {
      CORE_ADDR addr;
      struct value *val;

      annotate_display_format ();

      printf_filtered ("x/");
      if (d->format.count != 1)
	printf_filtered ("%d", d->format.count);
      printf_filtered ("%c", d->format.format);
      if (d->format.format != 'i' && d->format.format != 's')
	printf_filtered ("%c", d->format.size);
      printf_filtered (" ");

      annotate_display_expression ();

      print_expression (d->exp, gdb_stdout);
      annotate_display_expression_end ();

      if (d->format.count != 1)
	printf_filtered ("\n");
      else
	printf_filtered ("  ");

      val = evaluate_expression (d->exp);
      addr = value_as_address (val);
      if (d->format.format == 'i')
	addr = ADDR_BITS_REMOVE (addr);

      annotate_display_value ();

      do_examine (d->format, addr, VALUE_BFD_SECTION (val));
    }
  else
    {
      annotate_display_format ();

      if (d->format.format)
	printf_filtered ("/%c ", d->format.format);

      annotate_display_expression ();

      print_expression (d->exp, gdb_stdout);
      annotate_display_expression_end ();

      printf_filtered (" = ");

      annotate_display_expression ();

      print_formatted (evaluate_expression (d->exp),
		       d->format.format, d->format.size, gdb_stdout);
      printf_filtered ("\n");
    }

  annotate_display_end ();

  gdb_flush (gdb_stdout);
  current_display_number = -1;
}