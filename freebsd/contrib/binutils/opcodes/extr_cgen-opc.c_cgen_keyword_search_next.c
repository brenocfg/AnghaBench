#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__ const* next_name; } ;
struct TYPE_7__ {size_t current_hash; TYPE_3__ const* current_entry; TYPE_1__* table; } ;
struct TYPE_6__ {size_t hash_table_size; TYPE_3__ const** name_hash_table; } ;
typedef  TYPE_2__ CGEN_KEYWORD_SEARCH ;
typedef  TYPE_3__ CGEN_KEYWORD_ENTRY ;

/* Variables and functions */

const CGEN_KEYWORD_ENTRY *
cgen_keyword_search_next (CGEN_KEYWORD_SEARCH *search)
{
  /* Has search finished?  */
  if (search->current_hash == search->table->hash_table_size)
    return NULL;

  /* Search in progress?  */
  if (search->current_entry != NULL
      /* Anything left on this hash chain?  */
      && search->current_entry->next_name != NULL)
    {
      search->current_entry = search->current_entry->next_name;
      return search->current_entry;
    }

  /* Move to next hash chain [unless we haven't started yet].  */
  if (search->current_entry != NULL)
    ++search->current_hash;

  while (search->current_hash < search->table->hash_table_size)
    {
      search->current_entry = search->table->name_hash_table[search->current_hash];
      if (search->current_entry != NULL)
	return search->current_entry;
      ++search->current_hash;
    }

  return NULL;
}