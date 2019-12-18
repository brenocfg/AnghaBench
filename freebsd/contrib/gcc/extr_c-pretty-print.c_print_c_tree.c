#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int pp_needs_newline ;
typedef  int /*<<< orphan*/  c_pretty_printer ;
struct TYPE_5__ {TYPE_1__* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_2__* pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_pretty_printer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_construct (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_newline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
print_c_tree (FILE *file, tree t)
{
  static c_pretty_printer pp_rec;
  static bool initialized = 0;
  c_pretty_printer *pp = &pp_rec;

  if (!initialized)
    {
      initialized = 1;
      pp_construct (pp_base (pp), NULL, 0);
      pp_c_pretty_printer_init (pp);
      pp_needs_newline (pp) = true;
    }
  pp_base (pp)->buffer->stream = file;

  pp_statement (pp, t);

  pp_newline (pp);
  pp_flush (pp);
}