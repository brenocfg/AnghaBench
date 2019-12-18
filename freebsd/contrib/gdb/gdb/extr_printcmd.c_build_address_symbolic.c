#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtab_and_line {int line; TYPE_1__* symtab; } ;
struct symtab {char* filename; } ;
struct symbol {int line; } ;
struct minimal_symbol {int line; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {char* filename; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 char* SYMBOL_PRINT_NAME (struct symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 scalar_t__ asm_demangle ; 
 int /*<<< orphan*/ * find_pc_overlay (scalar_t__) ; 
 struct symbol* find_pc_sect_function (scalar_t__,int /*<<< orphan*/ *) ; 
 struct symtab_and_line find_pc_sect_line (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct symbol* lookup_minimal_symbol_by_pc_section (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ max_symbolic_offset ; 
 scalar_t__ overlay_debugging ; 
 scalar_t__ overlay_mapped_address (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ pc_in_unmapped_range (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ print_symbol_filename ; 
 char* xstrdup (char*) ; 

int
build_address_symbolic (CORE_ADDR addr,  /* IN */
			int do_demangle, /* IN */
			char **name,     /* OUT */
			int *offset,     /* OUT */
			char **filename, /* OUT */
			int *line,       /* OUT */
			int *unmapped)   /* OUT */
{
  struct minimal_symbol *msymbol;
  struct symbol *symbol;
  struct symtab *symtab = 0;
  CORE_ADDR name_location = 0;
  asection *section = 0;
  char *name_temp = "";
  
  /* Let's say it is unmapped. */
  *unmapped = 0;

  /* Determine if the address is in an overlay, and whether it is
     mapped. */
  if (overlay_debugging)
    {
      section = find_pc_overlay (addr);
      if (pc_in_unmapped_range (addr, section))
	{
	  *unmapped = 1;
	  addr = overlay_mapped_address (addr, section);
	}
    }

  /* First try to find the address in the symbol table, then
     in the minsyms.  Take the closest one.  */

  /* This is defective in the sense that it only finds text symbols.  So
     really this is kind of pointless--we should make sure that the
     minimal symbols have everything we need (by changing that we could
     save some memory, but for many debug format--ELF/DWARF or
     anything/stabs--it would be inconvenient to eliminate those minimal
     symbols anyway).  */
  msymbol = lookup_minimal_symbol_by_pc_section (addr, section);
  symbol = find_pc_sect_function (addr, section);

  if (symbol)
    {
      name_location = BLOCK_START (SYMBOL_BLOCK_VALUE (symbol));
      if (do_demangle || asm_demangle)
	name_temp = SYMBOL_PRINT_NAME (symbol);
      else
	name_temp = DEPRECATED_SYMBOL_NAME (symbol);
    }

  if (msymbol != NULL)
    {
      if (SYMBOL_VALUE_ADDRESS (msymbol) > name_location || symbol == NULL)
	{
	  /* The msymbol is closer to the address than the symbol;
	     use the msymbol instead.  */
	  symbol = 0;
	  symtab = 0;
	  name_location = SYMBOL_VALUE_ADDRESS (msymbol);
	  if (do_demangle || asm_demangle)
	    name_temp = SYMBOL_PRINT_NAME (msymbol);
	  else
	    name_temp = DEPRECATED_SYMBOL_NAME (msymbol);
	}
    }
  if (symbol == NULL && msymbol == NULL)
    return 1;

  /* If the nearest symbol is too far away, don't print anything symbolic.  */

  /* For when CORE_ADDR is larger than unsigned int, we do math in
     CORE_ADDR.  But when we detect unsigned wraparound in the
     CORE_ADDR math, we ignore this test and print the offset,
     because addr+max_symbolic_offset has wrapped through the end
     of the address space back to the beginning, giving bogus comparison.  */
  if (addr > name_location + max_symbolic_offset
      && name_location + max_symbolic_offset > name_location)
    return 1;

  *offset = addr - name_location;

  *name = xstrdup (name_temp);

  if (print_symbol_filename)
    {
      struct symtab_and_line sal;

      sal = find_pc_sect_line (addr, section, 0);

      if (sal.symtab)
	{
	  *filename = xstrdup (sal.symtab->filename);
	  *line = sal.line;
	}
      else if (symtab && symbol && symbol->line)
	{
	  *filename = xstrdup (symtab->filename);
	  *line = symbol->line;
	}
      else if (symtab)
	{
	  *filename = xstrdup (symtab->filename);
	  *line = -1;
	}
    }
  return 0;
}