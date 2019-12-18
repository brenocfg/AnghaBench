#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* htab_t ;
typedef  size_t hashval_t ;
struct TYPE_6__ {scalar_t__* entries; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 scalar_t__ HTAB_DELETED_ENTRY ; 
 scalar_t__ HTAB_EMPTY_ENTRY ; 
 int /*<<< orphan*/  abort () ; 
 size_t htab_mod (size_t,TYPE_1__*) ; 
 size_t htab_mod_m2 (size_t,TYPE_1__*) ; 
 size_t htab_size (TYPE_1__*) ; 

__attribute__((used)) static PTR *
find_empty_slot_for_expand (htab_t htab, hashval_t hash)
{
  hashval_t index = htab_mod (hash, htab);
  size_t size = htab_size (htab);
  PTR *slot = htab->entries + index;
  hashval_t hash2;

  if (*slot == HTAB_EMPTY_ENTRY)
    return slot;
  else if (*slot == HTAB_DELETED_ENTRY)
    abort ();

  hash2 = htab_mod_m2 (hash, htab);
  for (;;)
    {
      index += hash2;
      if (index >= size)
	index -= size;

      slot = htab->entries + index;
      if (*slot == HTAB_EMPTY_ENTRY)
	return slot;
      else if (*slot == HTAB_DELETED_ENTRY)
	abort ();
    }
}