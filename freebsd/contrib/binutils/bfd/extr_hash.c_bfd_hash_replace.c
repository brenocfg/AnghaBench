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
struct bfd_hash_table {unsigned int size; struct bfd_hash_entry** table; } ;
struct bfd_hash_entry {unsigned int hash; struct bfd_hash_entry* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 

void
bfd_hash_replace (struct bfd_hash_table *table,
		  struct bfd_hash_entry *old,
		  struct bfd_hash_entry *nw)
{
  unsigned int index;
  struct bfd_hash_entry **pph;

  index = old->hash % table->size;
  for (pph = &table->table[index];
       (*pph) != NULL;
       pph = &(*pph)->next)
    {
      if (*pph == old)
	{
	  *pph = nw;
	  return;
	}
    }

  abort ();
}