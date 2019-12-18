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
 int MSYMBOL_TYPE (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
#define  mst_file_text 128 
 int mst_text ; 
 unsigned int msymbol_hash (char const*) ; 
 struct objfile* object_files ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct minimal_symbol *
lookup_minimal_symbol_text (const char *name, struct objfile *objf)
{
  struct objfile *objfile;
  struct minimal_symbol *msymbol;
  struct minimal_symbol *found_symbol = NULL;
  struct minimal_symbol *found_file_symbol = NULL;

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
		  (MSYMBOL_TYPE (msymbol) == mst_text ||
		   MSYMBOL_TYPE (msymbol) == mst_file_text))
		{
		  switch (MSYMBOL_TYPE (msymbol))
		    {
		    case mst_file_text:
		      found_file_symbol = msymbol;
		      break;
		    default:
		      found_symbol = msymbol;
		      break;
		    }
		}
	    }
	}
    }
  /* External symbols are best.  */
  if (found_symbol)
    return found_symbol;

  /* File-local symbols are next best.  */
  if (found_file_symbol)
    return found_file_symbol;

  return NULL;
}