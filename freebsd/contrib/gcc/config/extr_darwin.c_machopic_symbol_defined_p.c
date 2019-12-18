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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ DECL_COMMON (int /*<<< orphan*/ ) ; 
 int MACHO_SYMBOL_FLAG_DEFINED ; 
 int MACHO_SYMBOL_FLAG_VARIABLE ; 
 int /*<<< orphan*/  SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_EXTERNAL_P (int /*<<< orphan*/ ) ; 
 int SYMBOL_REF_FLAGS (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
machopic_symbol_defined_p (rtx sym_ref)
{
  if (SYMBOL_REF_FLAGS (sym_ref) & MACHO_SYMBOL_FLAG_DEFINED)
    return true;

  /* If a symbol references local and is not an extern to this
     file, then the symbol might be able to declared as defined.  */
  if (SYMBOL_REF_LOCAL_P (sym_ref) && ! SYMBOL_REF_EXTERNAL_P (sym_ref))
    {
      /* If the symbol references a variable and the variable is a
	 common symbol, then this symbol is not defined.  */
      if (SYMBOL_REF_FLAGS (sym_ref) & MACHO_SYMBOL_FLAG_VARIABLE)
	{
	  tree decl = SYMBOL_REF_DECL (sym_ref);
	  if (!decl)
	    return true;
	  if (DECL_COMMON (decl))
	    return false;
	}
      return true;
    }
  return false;
}