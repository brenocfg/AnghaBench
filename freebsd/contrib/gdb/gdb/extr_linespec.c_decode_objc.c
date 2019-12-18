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
struct symtab_and_line {int /*<<< orphan*/  pc; scalar_t__ end; scalar_t__ line; scalar_t__ symtab; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR (struct symtab*) ; 
 struct block* BLOCKVECTOR_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LOC_BLOCK ; 
 int /*<<< orphan*/  STATIC_BLOCK ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_LINKAGE_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  build_canonical_line_spec (struct symtab_and_line*,int /*<<< orphan*/ ,char***) ; 
 struct symtabs_and_lines decode_line_2 (struct symbol**,int,int,char***) ; 
 struct symtab_and_line find_function_start_sal (struct symbol*,int) ; 
 char* find_imps (struct symtab*,struct block*,char*,struct symbol**,int*,int*) ; 
 struct symbol* find_pc_function (int /*<<< orphan*/ ) ; 
 struct block* get_selected_block (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

struct symtabs_and_lines
decode_objc (char **argptr, int funfirstline, struct symtab *file_symtab,
	     char ***canonical, char *saved_arg)
{
  struct symtabs_and_lines values;
  struct symbol **sym_arr = NULL;
  struct symbol *sym = NULL;
  char *copy = NULL;
  struct block *block = NULL;
  int i1 = 0;
  int i2 = 0;

  values.sals = NULL;
  values.nelts = 0;

  if (file_symtab != NULL)
    block = BLOCKVECTOR_BLOCK (BLOCKVECTOR (file_symtab), STATIC_BLOCK);
  else
    block = get_selected_block (0);
    
  copy = find_imps (file_symtab, block, *argptr, NULL, &i1, &i2); 
    
  if (i1 > 0)
    {
      sym_arr = (struct symbol **) alloca ((i1 + 1) * sizeof (struct symbol *));
      sym_arr[i1] = 0;

      copy = find_imps (file_symtab, block, *argptr, sym_arr, &i1, &i2); 
      *argptr = copy;
    }

  /* i1 now represents the TOTAL number of matches found.
     i2 represents how many HIGH-LEVEL (struct symbol) matches,
     which will come first in the sym_arr array.  Any low-level
     (minimal_symbol) matches will follow those.  */
      
  if (i1 == 1)
    {
      if (i2 > 0)
	{
	  /* Already a struct symbol.  */
	  sym = sym_arr[0];
	}
      else
	{
	  sym = find_pc_function (SYMBOL_VALUE_ADDRESS (sym_arr[0]));
	  if ((sym != NULL) && strcmp (SYMBOL_LINKAGE_NAME (sym_arr[0]), SYMBOL_LINKAGE_NAME (sym)) != 0)
	    {
	      warning ("debugging symbol \"%s\" does not match selector; ignoring", SYMBOL_LINKAGE_NAME (sym));
	      sym = NULL;
	    }
	}
	      
      values.sals = (struct symtab_and_line *) xmalloc (sizeof (struct symtab_and_line));
      values.nelts = 1;
	      
      if (sym && SYMBOL_CLASS (sym) == LOC_BLOCK)
	{
	  /* Canonicalize this, so it remains resolved for dylib loads.  */
	  values.sals[0] = find_function_start_sal (sym, funfirstline);
	  build_canonical_line_spec (values.sals, SYMBOL_NATURAL_NAME (sym), canonical);
	}
      else
	{
	  /* The only match was a non-debuggable symbol.  */
	  values.sals[0].symtab = 0;
	  values.sals[0].line = 0;
	  values.sals[0].end = 0;
	  values.sals[0].pc = SYMBOL_VALUE_ADDRESS (sym_arr[0]);
	}
      return values;
    }

  if (i1 > 1)
    {
      /* More than one match. The user must choose one or more.  */
      return decode_line_2 (sym_arr, i2, funfirstline, canonical);
    }

  return values;
}