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
struct symbol {struct symbol* hash_next; } ;
struct dictionary {int dummy; } ;

/* Variables and functions */
 struct symbol** DICT_HASHED_BUCKETS (struct dictionary*) ; 
 unsigned int DICT_HASHED_NBUCKETS (struct dictionary*) ; 
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct symbol*) ; 
 unsigned int msymbol_hash_iw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
insert_symbol_hashed (struct dictionary *dict,
		      struct symbol *sym)
{
  unsigned int hash_index;
  struct symbol **buckets = DICT_HASHED_BUCKETS (dict);

  hash_index = (msymbol_hash_iw (SYMBOL_NATURAL_NAME (sym))
		% DICT_HASHED_NBUCKETS (dict));
  sym->hash_next = buckets[hash_index];
  buckets[hash_index] = sym;
}