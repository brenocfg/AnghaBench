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
typedef  int /*<<< orphan*/  symbolS ;
struct local_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_CLEAR_WEAKREFD (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  local_hash ; 
 int /*<<< orphan*/  sy_hash ; 

symbolS *
symbol_find_exact_noref (const char *name, int noref)
{
  struct local_symbol *locsym;
  symbolS* sym;

  locsym = (struct local_symbol *) hash_find (local_hash, name);
  if (locsym != NULL)
    return (symbolS *) locsym;

  sym = ((symbolS *) hash_find (sy_hash, name));

  /* Any references to the symbol, except for the reference in
     .weakref, must clear this flag, such that the symbol does not
     turn into a weak symbol.  Note that we don't have to handle the
     local_symbol case, since a weakrefd is always promoted out of the
     local_symbol table when it is turned into a weak symbol.  */
  if (sym && ! noref)
    S_CLEAR_WEAKREFD (sym);

  return sym;
}