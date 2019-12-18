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
struct objfile {struct minimal_symbol** msymbol_demangled_hash; struct minimal_symbol** msymbol_hash; struct objfile* next; } ;
struct minimal_symbol {struct minimal_symbol* demangled_hash_next; struct minimal_symbol* hash_next; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 unsigned int MINIMAL_SYMBOL_HASH_SIZE ; 
 int MSYMBOL_TYPE (struct minimal_symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_DEMANGLED_NAME (struct minimal_symbol*) ; 
#define  mst_file_bss 132 
#define  mst_file_data 131 
#define  mst_file_text 130 
#define  mst_solib_trampoline 129 
#define  mst_unknown 128 
 unsigned int msymbol_hash (char const*) ; 
 unsigned int msymbol_hash_iw (char const*) ; 
 struct objfile* object_files ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp_iw (int /*<<< orphan*/ *,char const*) ; 
 char* strrchr (char const*,char) ; 

struct minimal_symbol *
lookup_minimal_symbol (const char *name, const char *sfile,
		       struct objfile *objf)
{
  struct objfile *objfile;
  struct minimal_symbol *msymbol;
  struct minimal_symbol *found_symbol = NULL;
  struct minimal_symbol *found_file_symbol = NULL;
  struct minimal_symbol *trampoline_symbol = NULL;

  unsigned int hash = msymbol_hash (name) % MINIMAL_SYMBOL_HASH_SIZE;
  unsigned int dem_hash = msymbol_hash_iw (name) % MINIMAL_SYMBOL_HASH_SIZE;

#ifdef SOFUN_ADDRESS_MAYBE_MISSING
  if (sfile != NULL)
    {
      char *p = strrchr (sfile, '/');
      if (p != NULL)
	sfile = p + 1;
    }
#endif

  for (objfile = object_files;
       objfile != NULL && found_symbol == NULL;
       objfile = objfile->next)
    {
      if (objf == NULL || objf == objfile)
	{
	  /* Do two passes: the first over the ordinary hash table,
	     and the second over the demangled hash table.  */
        int pass;

        for (pass = 1; pass <= 2 && found_symbol == NULL; pass++)
	    {
            /* Select hash list according to pass.  */
            if (pass == 1)
              msymbol = objfile->msymbol_hash[hash];
            else
              msymbol = objfile->msymbol_demangled_hash[dem_hash];

            while (msymbol != NULL && found_symbol == NULL)
		{
		  /* FIXME: carlton/2003-02-27: This is an unholy
		     mixture of linkage names and natural names.  If
		     you want to test the linkage names with strcmp,
		     do that.  If you want to test the natural names
		     with strcmp_iw, use SYMBOL_MATCHES_NATURAL_NAME.  */
		  if (strcmp (DEPRECATED_SYMBOL_NAME (msymbol), (name)) == 0
		      || (SYMBOL_DEMANGLED_NAME (msymbol) != NULL
			  && strcmp_iw (SYMBOL_DEMANGLED_NAME (msymbol),
					(name)) == 0))
		    {
                    switch (MSYMBOL_TYPE (msymbol))
                      {
                      case mst_file_text:
                      case mst_file_data:
                      case mst_file_bss:
#ifdef SOFUN_ADDRESS_MAYBE_MISSING
                        if (sfile == NULL
			    || strcmp (msymbol->filename, sfile) == 0)
                          found_file_symbol = msymbol;
#else
                        /* We have neither the ability nor the need to
                           deal with the SFILE parameter.  If we find
                           more than one symbol, just return the latest
                           one (the user can't expect useful behavior in
                           that case).  */
                        found_file_symbol = msymbol;
#endif
                        break;

                      case mst_solib_trampoline:

                        /* If a trampoline symbol is found, we prefer to
                           keep looking for the *real* symbol. If the
                           actual symbol is not found, then we'll use the
                           trampoline entry. */
                        if (trampoline_symbol == NULL)
                          trampoline_symbol = msymbol;
                        break;

                      case mst_unknown:
                      default:
                        found_symbol = msymbol;
                        break;
                      }
		    }

                /* Find the next symbol on the hash chain.  */
                if (pass == 1)
                  msymbol = msymbol->hash_next;
                else
                  msymbol = msymbol->demangled_hash_next;
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

  /* Symbols for shared library trampolines are next best.  */
  if (trampoline_symbol)
    return trampoline_symbol;

  return NULL;
}