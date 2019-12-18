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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {scalar_t__ line; struct symtab* symtab; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct blockvector {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct blockvector* BLOCKVECTOR (struct symtab*) ; 
 struct block* BLOCKVECTOR_BLOCK (struct blockvector*,int /*<<< orphan*/ ) ; 
 scalar_t__ LOC_BLOCK ; 
 int /*<<< orphan*/  STATIC_BLOCK ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 scalar_t__ SYMBOL_LINE (struct symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  build_canonical_line_spec (struct symtab_and_line*,char*,char***) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 struct symtab_and_line find_function_start_sal (struct symbol*,int) ; 
 int /*<<< orphan*/ * lookup_block_symbol (struct block*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct symtab_and_line*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct symtabs_and_lines
symbol_found (int funfirstline, char ***canonical, char *copy,
	      struct symbol *sym, struct symtab *file_symtab,
	      struct symtab *sym_symtab)
{
  struct symtabs_and_lines values;
  
  if (SYMBOL_CLASS (sym) == LOC_BLOCK)
    {
      /* Arg is the name of a function */
      values.sals = (struct symtab_and_line *)
	xmalloc (sizeof (struct symtab_and_line));
      values.sals[0] = find_function_start_sal (sym, funfirstline);
      values.nelts = 1;

      /* Don't use the SYMBOL_LINE; if used at all it points to
	 the line containing the parameters or thereabouts, not
	 the first line of code.  */

      /* We might need a canonical line spec if it is a static
	 function.  */
      if (file_symtab == 0)
	{
	  struct blockvector *bv = BLOCKVECTOR (sym_symtab);
	  struct block *b = BLOCKVECTOR_BLOCK (bv, STATIC_BLOCK);
	  if (lookup_block_symbol (b, copy, NULL, VAR_DOMAIN) != NULL)
	    build_canonical_line_spec (values.sals, copy, canonical);
	}
      return values;
    }
  else
    {
      if (funfirstline)
	error ("\"%s\" is not a function", copy);
      else if (SYMBOL_LINE (sym) != 0)
	{
	  /* We know its line number.  */
	  values.sals = (struct symtab_and_line *)
	    xmalloc (sizeof (struct symtab_and_line));
	  values.nelts = 1;
	  memset (&values.sals[0], 0, sizeof (values.sals[0]));
	  values.sals[0].symtab = sym_symtab;
	  values.sals[0].line = SYMBOL_LINE (sym);
	  return values;
	}
      else
	/* This can happen if it is compiled with a compiler which doesn't
	   put out line numbers for variables.  */
	/* FIXME: Shouldn't we just set .line and .symtab to zero
	   and return?  For example, "info line foo" could print
	   the address.  */
	error ("Line number not known for symbol \"%s\"", copy);
    }
}