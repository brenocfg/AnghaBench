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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  maybe_init_pretty_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

void
print_generic_stmt_indented (FILE *file, tree t, int flags, int indent)
{
  int i;

  maybe_init_pretty_print (file);

  for (i = 0; i < indent; i++)
    pp_space (&buffer);
  dump_generic_node (&buffer, t, indent, flags, true);
  pp_flush (&buffer);
}