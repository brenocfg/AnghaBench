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
struct macro_table {int /*<<< orphan*/  definitions; int /*<<< orphan*/  main_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_macro_source_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_delete (int /*<<< orphan*/ ) ; 

void
free_macro_table (struct macro_table *table)
{
  /* Free the source file tree.  */
  free_macro_source_file (table->main_source);

  /* Free the table of macro definitions.  */
  splay_tree_delete (table->definitions);
}