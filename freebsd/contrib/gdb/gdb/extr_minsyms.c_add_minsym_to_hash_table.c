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
struct minimal_symbol {struct minimal_symbol* hash_next; } ;

/* Variables and functions */
 unsigned int MINIMAL_SYMBOL_HASH_SIZE ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 unsigned int msymbol_hash (int /*<<< orphan*/ ) ; 

void
add_minsym_to_hash_table (struct minimal_symbol *sym,
			  struct minimal_symbol **table)
{
  if (sym->hash_next == NULL)
    {
      unsigned int hash
	= msymbol_hash (SYMBOL_LINKAGE_NAME (sym)) % MINIMAL_SYMBOL_HASH_SIZE;
      sym->hash_next = table[hash];
      table[hash] = sym;
    }
}