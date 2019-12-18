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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  compare_classes ; 
 int /*<<< orphan*/  find_methods (struct symtab*,char,char*,char*,char*,struct symbol**,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symbol* lookup_symbol (char*,struct block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* parse_method (char*,char*,char**,char**,char**) ; 
 char* parse_selector (char*,char**) ; 
 int /*<<< orphan*/  qsort (struct symbol**,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

char *find_imps (struct symtab *symtab, struct block *block,
		 char *method, struct symbol **syms, 
		 unsigned int *nsym, unsigned int *ndebug)
{
  char type = '\0';
  char *class = NULL;
  char *category = NULL;
  char *selector = NULL;

  unsigned int csym = 0;
  unsigned int cdebug = 0;

  unsigned int ncsym = 0;
  unsigned int ncdebug = 0;

  char *buf = NULL;
  char *tmp = NULL;

  gdb_assert (nsym != NULL);
  gdb_assert (ndebug != NULL);

  if (nsym != NULL)
    *nsym = 0;
  if (ndebug != NULL)
    *ndebug = 0;

  buf = (char *) alloca (strlen (method) + 1);
  strcpy (buf, method);
  tmp = parse_method (buf, &type, &class, &category, &selector);

  if (tmp == NULL) {
    
    struct symbol *sym = NULL;
    struct minimal_symbol *msym = NULL;
    
    strcpy (buf, method);
    tmp = parse_selector (buf, &selector);
    
    if (tmp == NULL)
      return NULL;
    
    sym = lookup_symbol (selector, block, VAR_DOMAIN, 0, NULL);
    if (sym != NULL) 
      {
	if (syms)
	  syms[csym] = sym;
	csym++;
	cdebug++;
      }

    if (sym == NULL)
      msym = lookup_minimal_symbol (selector, 0, 0);

    if (msym != NULL) 
      {
	if (syms)
	  syms[csym] = (struct symbol *)msym;
	csym++;
      }
  }

  if (syms != NULL)
    find_methods (symtab, type, class, category, selector, 
		  syms + csym, &ncsym, &ncdebug);
  else
    find_methods (symtab, type, class, category, selector, 
		  NULL, &ncsym, &ncdebug);

  /* If we didn't find any methods, just return.  */
  if (ncsym == 0 && ncdebug == 0)
    return method;

  /* Take debug symbols from the second batch of symbols and swap them
   * with debug symbols from the first batch.  Repeat until either the
   * second section is out of debug symbols or the first section is
   * full of debug symbols.  Either way we have all debug symbols
   * packed to the beginning of the buffer.  
   */

  if (syms != NULL) 
    {
      while ((cdebug < csym) && (ncdebug > 0))
	{
	  struct symbol *s = NULL;
	  /* First non-debugging symbol.  */
	  unsigned int i = cdebug;
	  /* Last of second batch of debug symbols.  */
	  unsigned int j = csym + ncdebug - 1;

	  s = syms[j];
	  syms[j] = syms[i];
	  syms[i] = s;

	  /* We've moved a symbol from the second debug section to the
             first one.  */
	  cdebug++;
	  ncdebug--;
	}
    }

  csym += ncsym;
  cdebug += ncdebug;

  if (nsym != NULL)
    *nsym = csym;
  if (ndebug != NULL)
    *ndebug = cdebug;

  if (syms == NULL)
    return method + (tmp - buf);

  if (csym > 1)
    {
      /* Sort debuggable symbols.  */
      if (cdebug > 1)
	qsort (syms, cdebug, sizeof (struct minimal_symbol *), 
	       compare_classes);
      
      /* Sort minimal_symbols.  */
      if ((csym - cdebug) > 1)
	qsort (&syms[cdebug], csym - cdebug, 
	       sizeof (struct minimal_symbol *), compare_classes);
    }
  /* Terminate the sym_arr list.  */
  syms[csym] = 0;

  return method + (tmp - buf);
}