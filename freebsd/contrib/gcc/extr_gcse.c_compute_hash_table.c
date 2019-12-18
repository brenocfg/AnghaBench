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
struct hash_table {int size; int /*<<< orphan*/  table; scalar_t__ n_elems; } ;
struct expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_hash_table_work (struct hash_table*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
compute_hash_table (struct hash_table *table)
{
  /* Initialize count of number of entries in hash table.  */
  table->n_elems = 0;
  memset (table->table, 0, table->size * sizeof (struct expr *));

  compute_hash_table_work (table);
}