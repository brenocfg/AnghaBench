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
struct symtabs_and_lines {int dummy; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKVECTOR (struct symtab*) ; 
 int /*<<< orphan*/  BLOCKVECTOR_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATIC_BLOCK ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_silent (char*,char*) ; 
 int /*<<< orphan*/  get_selected_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_full_symbols () ; 
 int /*<<< orphan*/  have_minimal_symbols () ; 
 int /*<<< orphan*/  have_partial_symbols () ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 
 struct symtabs_and_lines minsym_found (int,struct minimal_symbol*) ; 
 struct symtabs_and_lines symbol_found (int,char***,char*,struct symbol*,struct symtab*,struct symtab*) ; 

__attribute__((used)) static struct symtabs_and_lines
decode_variable (char *copy, int funfirstline, char ***canonical,
		 struct symtab *file_symtab, int *not_found_ptr)
{
  struct symbol *sym;
  /* The symtab that SYM was found in.  */
  struct symtab *sym_symtab;

  struct minimal_symbol *msymbol;

  sym = lookup_symbol (copy,
		       (file_symtab
			? BLOCKVECTOR_BLOCK (BLOCKVECTOR (file_symtab),
					     STATIC_BLOCK)
			: get_selected_block (0)),
		       VAR_DOMAIN, 0, &sym_symtab);

  if (sym != NULL)
    return symbol_found (funfirstline, canonical, copy, sym,
			 file_symtab, sym_symtab);

  msymbol = lookup_minimal_symbol (copy, NULL, NULL);

  if (msymbol != NULL)
    return minsym_found (funfirstline, msymbol);

  if (!have_full_symbols () &&
      !have_partial_symbols () && !have_minimal_symbols ())
    error ("No symbol table is loaded.  Use the \"file\" command.");

  if (not_found_ptr)
    {
      *not_found_ptr = 1;
      /* The caller has indicated that it wishes quiet notification of any
	 error where the function or file is not found.  A call to 
	 error_silent causes an error to occur, but it does not issue 
	 the supplied message.  The message can be manually output by
	 the caller, if desired.  This is used, for example, when 
	 attempting to set breakpoints for functions in shared libraries 
	 that have not yet been loaded.  */
      error_silent ("Function \"%s\" not defined.", copy);
    }
  
  error ("Function \"%s\" not defined.", copy);
}