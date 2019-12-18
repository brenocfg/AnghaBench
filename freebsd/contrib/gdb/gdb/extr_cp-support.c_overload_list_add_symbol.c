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
struct symbol {int dummy; } ;

/* Variables and functions */
 char const* SYMBOL_LINKAGE_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_NATURAL_NAME (struct symbol*) ; 
 int /*<<< orphan*/ * SYMBOL_TYPE (struct symbol*) ; 
 char* remove_params (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 struct symbol** sym_return_val ; 
 int sym_return_val_index ; 
 int sym_return_val_size ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static void
overload_list_add_symbol (struct symbol *sym, const char *oload_name)
{
  int newsize;
  int i;
  char *sym_name;

  /* If there is no type information, we can't do anything, so skip */
  if (SYMBOL_TYPE (sym) == NULL)
    return;

  /* skip any symbols that we've already considered. */
  for (i = 0; i < sym_return_val_index; ++i)
    if (strcmp (SYMBOL_LINKAGE_NAME (sym),
		SYMBOL_LINKAGE_NAME (sym_return_val[i])) == 0)
      return;

  /* Get the demangled name without parameters */
  sym_name = remove_params (SYMBOL_NATURAL_NAME (sym));
  if (!sym_name)
    return;

  /* skip symbols that cannot match */
  if (strcmp (sym_name, oload_name) != 0)
    {
      xfree (sym_name);
      return;
    }

  xfree (sym_name);

  /* We have a match for an overload instance, so add SYM to the current list
   * of overload instances */
  if (sym_return_val_index + 3 > sym_return_val_size)
    {
      newsize = (sym_return_val_size *= 2) * sizeof (struct symbol *);
      sym_return_val = (struct symbol **) xrealloc ((char *) sym_return_val, newsize);
    }
  sym_return_val[sym_return_val_index++] = sym;
  sym_return_val[sym_return_val_index] = NULL;
}