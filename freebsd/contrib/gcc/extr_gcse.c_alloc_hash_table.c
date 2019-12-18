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
struct hash_table {int size; int set_p; int /*<<< orphan*/  table; } ;
struct expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmalloc (int) ; 

__attribute__((used)) static void
alloc_hash_table (int n_insns, struct hash_table *table, int set_p)
{
  int n;

  table->size = n_insns / 4;
  if (table->size < 11)
    table->size = 11;

  /* Attempt to maintain efficient use of hash table.
     Making it an odd number is simplest for now.
     ??? Later take some measurements.  */
  table->size |= 1;
  n = table->size * sizeof (struct expr *);
  table->table = gmalloc (n);
  table->set_p = set_p;
}