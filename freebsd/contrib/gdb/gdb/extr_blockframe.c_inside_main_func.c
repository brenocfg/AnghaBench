#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct obj_section {scalar_t__ endaddr; } ;
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_4__ {scalar_t__ main_func_lowpc; scalar_t__ main_func_highpc; } ;
struct TYPE_5__ {TYPE_1__ ei; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BLOCK_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_ENTRY_HIGHPC ; 
 scalar_t__ INVALID_ENTRY_LOWPC ; 
 scalar_t__ LOC_BLOCK ; 
 scalar_t__ MSYMBOL_TYPE (struct minimal_symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_BFD_SECTION (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_LINKAGE_NAME (struct minimal_symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct symbol* find_pc_function (scalar_t__) ; 
 struct obj_section* find_pc_sect_section (scalar_t__,int /*<<< orphan*/ *) ; 
 struct minimal_symbol* lookup_minimal_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  main_name () ; 
 scalar_t__ mst_text ; 
 TYPE_2__* symfile_objfile ; 

int
inside_main_func (CORE_ADDR pc)
{
  struct minimal_symbol *msymbol;

  if (symfile_objfile == 0)
    return 0;

  msymbol = lookup_minimal_symbol (main_name (), NULL, symfile_objfile);

  /* If the address range hasn't been set up at symbol reading time,
     set it up now.  */

  if (msymbol != NULL
      && symfile_objfile->ei.main_func_lowpc == INVALID_ENTRY_LOWPC
      && symfile_objfile->ei.main_func_highpc == INVALID_ENTRY_HIGHPC)
    {
      /* brobecker/2003-10-10: We used to rely on lookup_symbol() to
	 search the symbol associated to the "main" function.
	 Unfortunately, lookup_symbol() uses the current-language
	 la_lookup_symbol_nonlocal function to do the global symbol
	 search.  Depending on the language, this can introduce
	 certain side-effects, because certain languages, for instance
	 Ada, may find more than one match.  Therefore we prefer to
	 search the "main" function symbol using its address rather
	 than its name.  */
      struct symbol *mainsym =
	find_pc_function (SYMBOL_VALUE_ADDRESS (msymbol));

      if (mainsym && SYMBOL_CLASS (mainsym) == LOC_BLOCK)
	{
	  symfile_objfile->ei.main_func_lowpc =
	    BLOCK_START (SYMBOL_BLOCK_VALUE (mainsym));
	  symfile_objfile->ei.main_func_highpc =
	    BLOCK_END (SYMBOL_BLOCK_VALUE (mainsym));
	}
    }

  /* Not in the normal symbol tables, see if "main" is in the partial
     symbol table.  If it's not, then give up.  */
  if (msymbol != NULL && MSYMBOL_TYPE (msymbol) == mst_text)
    {
      CORE_ADDR maddr = SYMBOL_VALUE_ADDRESS (msymbol);
      asection *msect = SYMBOL_BFD_SECTION (msymbol);
      struct obj_section *osect = find_pc_sect_section (maddr, msect);

      if (osect != NULL)
	{
	  int i;

	  /* Step over other symbols at this same address, and symbols
	     in other sections, to find the next symbol in this
	     section with a different address.  */
	  for (i = 1; SYMBOL_LINKAGE_NAME (msymbol + i) != NULL; i++)
	    {
	      if (SYMBOL_VALUE_ADDRESS (msymbol + i) != maddr
		  && SYMBOL_BFD_SECTION (msymbol + i) == msect)
		break;
	    }

	  symfile_objfile->ei.main_func_lowpc = maddr;

	  /* Use the lesser of the next minimal symbol in the same
	     section, or the end of the section, as the end of the
	     function.  */
	  if (SYMBOL_LINKAGE_NAME (msymbol + i) != NULL
	      && SYMBOL_VALUE_ADDRESS (msymbol + i) < osect->endaddr)
	    symfile_objfile->ei.main_func_highpc =
	      SYMBOL_VALUE_ADDRESS (msymbol + i);
	  else
	    /* We got the start address from the last msymbol in the
	       objfile.  So the end address is the end of the
	       section.  */
	    symfile_objfile->ei.main_func_highpc = osect->endaddr;
	}
    }

  return (symfile_objfile->ei.main_func_lowpc <= pc
	  && symfile_objfile->ei.main_func_highpc > pc);
}