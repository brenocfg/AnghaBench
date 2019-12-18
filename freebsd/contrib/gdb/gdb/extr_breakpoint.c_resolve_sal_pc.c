#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symtab_and_line {scalar_t__ section; int /*<<< orphan*/  pc; TYPE_1__* symtab; int /*<<< orphan*/  line; } ;
struct symbol {int dummy; } ;
typedef  struct symbol minimal_symbol ;
struct blockvector {int dummy; } ;
struct block {int dummy; } ;
struct TYPE_3__ {char* filename; int /*<<< orphan*/  objfile; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int) ; 
 void* SYMBOL_BFD_SECTION (struct symbol*) ; 
 struct symbol* block_function (struct block*) ; 
 struct blockvector* blockvector_for_pc_sect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  find_line_pc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixup_symbol_section (struct symbol*,int /*<<< orphan*/ ) ; 
 struct symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 

void
resolve_sal_pc (struct symtab_and_line *sal)
{
  CORE_ADDR pc;

  if (sal->pc == 0 && sal->symtab != NULL)
    {
      if (!find_line_pc (sal->symtab, sal->line, &pc))
	error ("No line %d in file \"%s\".",
	       sal->line, sal->symtab->filename);
      sal->pc = pc;
    }

  if (sal->section == 0 && sal->symtab != NULL)
    {
      struct blockvector *bv;
      struct block *b;
      struct symbol *sym;
      int index;

      bv = blockvector_for_pc_sect (sal->pc, 0, &index, sal->symtab);
      if (bv != NULL)
	{
	  b = BLOCKVECTOR_BLOCK (bv, index);
	  sym = block_function (b);
	  if (sym != NULL)
	    {
	      fixup_symbol_section (sym, sal->symtab->objfile);
	      sal->section = SYMBOL_BFD_SECTION (sym);
	    }
	  else
	    {
	      /* It really is worthwhile to have the section, so we'll just
	         have to look harder. This case can be executed if we have 
	         line numbers but no functions (as can happen in assembly 
	         source).  */

	      struct minimal_symbol *msym;

	      msym = lookup_minimal_symbol_by_pc (sal->pc);
	      if (msym)
		sal->section = SYMBOL_BFD_SECTION (msym);
	    }
	}
    }
}