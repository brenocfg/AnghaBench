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
struct table_elt {struct table_elt* next_same_hash; struct table_elt* related_value; struct table_elt* prev_same_hash; struct table_elt* next_same_value; struct table_elt* first_same_value; struct table_elt* prev_same_value; } ;

/* Variables and functions */
 unsigned int HASH_SIZE ; 
 struct table_elt* free_element_chain ; 
 struct table_elt** table ; 
 int /*<<< orphan*/  table_size ; 

__attribute__((used)) static void
remove_from_table (struct table_elt *elt, unsigned int hash)
{
  if (elt == 0)
    return;

  /* Mark this element as removed.  See cse_insn.  */
  elt->first_same_value = 0;

  /* Remove the table element from its equivalence class.  */

  {
    struct table_elt *prev = elt->prev_same_value;
    struct table_elt *next = elt->next_same_value;

    if (next)
      next->prev_same_value = prev;

    if (prev)
      prev->next_same_value = next;
    else
      {
	struct table_elt *newfirst = next;
	while (next)
	  {
	    next->first_same_value = newfirst;
	    next = next->next_same_value;
	  }
      }
  }

  /* Remove the table element from its hash bucket.  */

  {
    struct table_elt *prev = elt->prev_same_hash;
    struct table_elt *next = elt->next_same_hash;

    if (next)
      next->prev_same_hash = prev;

    if (prev)
      prev->next_same_hash = next;
    else if (table[hash] == elt)
      table[hash] = next;
    else
      {
	/* This entry is not in the proper hash bucket.  This can happen
	   when two classes were merged by `merge_equiv_classes'.  Search
	   for the hash bucket that it heads.  This happens only very
	   rarely, so the cost is acceptable.  */
	for (hash = 0; hash < HASH_SIZE; hash++)
	  if (table[hash] == elt)
	    table[hash] = next;
      }
  }

  /* Remove the table element from its related-value circular chain.  */

  if (elt->related_value != 0 && elt->related_value != elt)
    {
      struct table_elt *p = elt->related_value;

      while (p->related_value != elt)
	p = p->related_value;
      p->related_value = elt->related_value;
      if (p->related_value == p)
	p->related_value = 0;
    }

  /* Now add it to the free element chain.  */
  elt->next_same_hash = free_element_chain;
  free_element_chain = elt;

  table_size--;
}