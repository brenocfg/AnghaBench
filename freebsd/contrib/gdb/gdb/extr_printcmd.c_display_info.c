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
struct TYPE_2__ {char size; scalar_t__ format; int /*<<< orphan*/  count; } ;
struct display {scalar_t__ block; int /*<<< orphan*/  exp; TYPE_1__ format; scalar_t__ enabled_p; int /*<<< orphan*/  number; struct display* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  contained_in (int /*<<< orphan*/ ,scalar_t__) ; 
 struct display* display_chain ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
display_info (char *ignore, int from_tty)
{
  struct display *d;

  if (!display_chain)
    printf_unfiltered ("There are no auto-display expressions now.\n");
  else
    printf_filtered ("Auto-display expressions now in effect:\n\
Num Enb Expression\n");

  for (d = display_chain; d; d = d->next)
    {
      printf_filtered ("%d:   %c  ", d->number, "ny"[(int) d->enabled_p]);
      if (d->format.size)
	printf_filtered ("/%d%c%c ", d->format.count, d->format.size,
			 d->format.format);
      else if (d->format.format)
	printf_filtered ("/%c ", d->format.format);
      print_expression (d->exp, gdb_stdout);
      if (d->block && !contained_in (get_selected_block (0), d->block))
	printf_filtered (" (cannot be evaluated in the current context)");
      printf_filtered ("\n");
      gdb_flush (gdb_stdout);
    }
}