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
 int /*<<< orphan*/  dump_hash_table_entry ; 
 int /*<<< orphan*/  expr_table ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  htab_collisions (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_hash_table (FILE *file)
{
  fprintf (file, "\n\nexpression hash table\n");
  fprintf (file, "size %ld, %ld elements, %f collision/search ratio\n",
           (long) htab_size (expr_table),
           (long) htab_elements (expr_table),
           htab_collisions (expr_table));
  if (htab_elements (expr_table) > 0)
    {
      fprintf (file, "\n\ntable entries:\n");
      htab_traverse (expr_table, dump_hash_table_entry, file);
    }
  fprintf (file, "\n");
}