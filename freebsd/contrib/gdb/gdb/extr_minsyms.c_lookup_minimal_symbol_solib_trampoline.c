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
struct objfile {struct minimal_symbol** msymbol_hash; struct objfile* next; } ;
struct minimal_symbol {struct minimal_symbol* hash_next; } ;

/* Variables and functions */
 unsigned int MINIMAL_SYMBOL_HASH_SIZE ; 
 scalar_t__ MSYMBOL_TYPE (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 scalar_t__ mst_solib_trampoline ; 
 unsigned int msymbol_hash (char const*) ; 
 struct objfile* object_files ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct minimal_symbol *
lookup_minimal_symbol_solib_trampoline (const char *name,
					struct objfile *objf)
{
  struct objfile *objfile;
  struct minimal_symbol *msymbol;
  struct minimal_symbol *found_symbol = NULL;

  unsigned int hash = msymbol_hash (name) % MINIMAL_SYMBOL_HASH_SIZE;

  for (objfile = object_files;
       objfile != NULL && found_symbol == NULL;
       objfile = objfile->next)
    {
      if (objf == NULL || objf == objfile)
	{
	  for (msymbol = objfile->msymbol_hash[hash];
	       msymbol != NULL && found_symbol == NULL;
	       msymbol = msymbol->hash_next)
	    {
	      if (strcmp (SYMBOL_LINKAGE_NAME (msymbol), name) == 0 &&
		  MSYMBOL_TYPE (msymbol) == mst_solib_trampoline)
		return msymbol;
	    }
	}
    }

  return NULL;
}