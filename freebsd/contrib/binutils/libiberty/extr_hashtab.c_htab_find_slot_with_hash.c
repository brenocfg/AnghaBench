#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* htab_t ;
typedef  size_t hashval_t ;
typedef  enum insert_option { ____Placeholder_insert_option } insert_option ;
struct TYPE_7__ {int n_elements; scalar_t__* entries; int /*<<< orphan*/  n_deleted; scalar_t__ (* eq_f ) (scalar_t__,scalar_t__ const) ;int /*<<< orphan*/  collisions; int /*<<< orphan*/  searches; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 scalar_t__ HTAB_DELETED_ENTRY ; 
 scalar_t__ HTAB_EMPTY_ENTRY ; 
 int INSERT ; 
 int NO_INSERT ; 
 scalar_t__ htab_expand (TYPE_1__*) ; 
 size_t htab_mod (size_t,TYPE_1__*) ; 
 size_t htab_mod_m2 (size_t,TYPE_1__*) ; 
 size_t htab_size (TYPE_1__*) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__ const) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__ const) ; 

PTR *
htab_find_slot_with_hash (htab_t htab, const PTR element,
                          hashval_t hash, enum insert_option insert)
{
  PTR *first_deleted_slot;
  hashval_t index, hash2;
  size_t size;
  PTR entry;

  size = htab_size (htab);
  if (insert == INSERT && size * 3 <= htab->n_elements * 4)
    {
      if (htab_expand (htab) == 0)
	return NULL;
      size = htab_size (htab);
    }

  index = htab_mod (hash, htab);

  htab->searches++;
  first_deleted_slot = NULL;

  entry = htab->entries[index];
  if (entry == HTAB_EMPTY_ENTRY)
    goto empty_entry;
  else if (entry == HTAB_DELETED_ENTRY)
    first_deleted_slot = &htab->entries[index];
  else if ((*htab->eq_f) (entry, element))
    return &htab->entries[index];
      
  hash2 = htab_mod_m2 (hash, htab);
  for (;;)
    {
      htab->collisions++;
      index += hash2;
      if (index >= size)
	index -= size;
      
      entry = htab->entries[index];
      if (entry == HTAB_EMPTY_ENTRY)
	goto empty_entry;
      else if (entry == HTAB_DELETED_ENTRY)
	{
	  if (!first_deleted_slot)
	    first_deleted_slot = &htab->entries[index];
	}
      else if ((*htab->eq_f) (entry, element))
	return &htab->entries[index];
    }

 empty_entry:
  if (insert == NO_INSERT)
    return NULL;

  if (first_deleted_slot)
    {
      htab->n_deleted--;
      *first_deleted_slot = HTAB_EMPTY_ENTRY;
      return first_deleted_slot;
    }

  htab->n_elements++;
  return &htab->entries[index];
}