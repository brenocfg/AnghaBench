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
struct macro_source_file {int /*<<< orphan*/  table; scalar_t__ filename; struct macro_source_file* next_included; struct macro_source_file* includes; } ;

/* Variables and functions */
 int /*<<< orphan*/  macro_bcache_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  macro_free (struct macro_source_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_macro_source_file (struct macro_source_file *src)
{
  struct macro_source_file *child, *next_child;

  /* Free this file's children.  */
  for (child = src->includes; child; child = next_child)
    {
      next_child = child->next_included;
      free_macro_source_file (child);
    }

  macro_bcache_free (src->table, (char *) src->filename);
  macro_free (src, src->table);
}