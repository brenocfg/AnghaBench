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

/* Variables and functions */
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_silent (char*,char*) ; 
 int /*<<< orphan*/  have_full_symbols () ; 
 int /*<<< orphan*/  have_partial_symbols () ; 
 struct symtab* lookup_symtab (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static struct symtab *
symtab_from_filename (char **argptr, char *p, int is_quote_enclosed, 
		      int *not_found_ptr)
{
  char *p1;
  char *copy;
  struct symtab *file_symtab;
  
  p1 = p;
  while (p != *argptr && p[-1] == ' ')
    --p;
  if ((*p == '"') && is_quote_enclosed)
    --p;
  copy = (char *) alloca (p - *argptr + 1);
  memcpy (copy, *argptr, p - *argptr);
  /* It may have the ending quote right after the file name.  */
  if (is_quote_enclosed && copy[p - *argptr - 1] == '"')
    copy[p - *argptr - 1] = 0;
  else
    copy[p - *argptr] = 0;

  /* Find that file's data.  */
  file_symtab = lookup_symtab (copy);
  if (file_symtab == 0)
    {
      if (!have_full_symbols () && !have_partial_symbols ())
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
	  error_silent ("No source file named %s.", copy);
	}
      error ("No source file named %s.", copy);
    }

  /* Discard the file name from the arg.  */
  p = p1 + 1;
  while (*p == ' ' || *p == '\t')
    p++;
  *argptr = p;

  return file_symtab;
}