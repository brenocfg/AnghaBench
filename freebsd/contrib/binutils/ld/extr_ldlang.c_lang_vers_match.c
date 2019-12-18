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
struct bfd_elf_version_expr_head {int mask; struct bfd_elf_version_expr* remaining; scalar_t__ htab; } ;
struct bfd_elf_version_expr {char const* symbol; int mask; char* pattern; struct bfd_elf_version_expr* next; } ;

/* Variables and functions */
#define  BFD_ELF_VERSION_CXX_TYPE 129 
#define  BFD_ELF_VERSION_C_TYPE 128 
 int BFD_ELF_VERSION_JAVA_TYPE ; 
 int DMGL_ANSI ; 
 int DMGL_JAVA ; 
 int DMGL_PARAMS ; 
 char* cplus_demangle (char const*,int) ; 
 scalar_t__ fnmatch (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct bfd_elf_version_expr* htab_find (scalar_t__,struct bfd_elf_version_expr*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static struct bfd_elf_version_expr *
lang_vers_match (struct bfd_elf_version_expr_head *head,
		 struct bfd_elf_version_expr *prev,
		 const char *sym)
{
  const char *cxx_sym = sym;
  const char *java_sym = sym;
  struct bfd_elf_version_expr *expr = NULL;

  if (head->mask & BFD_ELF_VERSION_CXX_TYPE)
    {
      cxx_sym = cplus_demangle (sym, DMGL_PARAMS | DMGL_ANSI);
      if (!cxx_sym)
	cxx_sym = sym;
    }
  if (head->mask & BFD_ELF_VERSION_JAVA_TYPE)
    {
      java_sym = cplus_demangle (sym, DMGL_JAVA);
      if (!java_sym)
	java_sym = sym;
    }

  if (head->htab && (prev == NULL || prev->symbol))
    {
      struct bfd_elf_version_expr e;

      switch (prev ? prev->mask : 0)
	{
	  case 0:
	    if (head->mask & BFD_ELF_VERSION_C_TYPE)
	      {
		e.symbol = sym;
		expr = htab_find (head->htab, &e);
		while (expr && strcmp (expr->symbol, sym) == 0)
		  if (expr->mask == BFD_ELF_VERSION_C_TYPE)
		    goto out_ret;
		  else
		    expr = expr->next;
	      }
	    /* Fallthrough */
	  case BFD_ELF_VERSION_C_TYPE:
	    if (head->mask & BFD_ELF_VERSION_CXX_TYPE)
	      {
		e.symbol = cxx_sym;
		expr = htab_find (head->htab, &e);
		while (expr && strcmp (expr->symbol, cxx_sym) == 0)
		  if (expr->mask == BFD_ELF_VERSION_CXX_TYPE)
		    goto out_ret;
		  else
		    expr = expr->next;
	      }
	    /* Fallthrough */
	  case BFD_ELF_VERSION_CXX_TYPE:
	    if (head->mask & BFD_ELF_VERSION_JAVA_TYPE)
	      {
		e.symbol = java_sym;
		expr = htab_find (head->htab, &e);
		while (expr && strcmp (expr->symbol, java_sym) == 0)
		  if (expr->mask == BFD_ELF_VERSION_JAVA_TYPE)
		    goto out_ret;
		  else
		    expr = expr->next;
	      }
	    /* Fallthrough */
	  default:
	    break;
	}
    }

  /* Finally, try the wildcards.  */
  if (prev == NULL || prev->symbol)
    expr = head->remaining;
  else
    expr = prev->next;
  for (; expr; expr = expr->next)
    {
      const char *s;

      if (!expr->pattern)
	continue;

      if (expr->pattern[0] == '*' && expr->pattern[1] == '\0')
	break;

      if (expr->mask == BFD_ELF_VERSION_JAVA_TYPE)
	s = java_sym;
      else if (expr->mask == BFD_ELF_VERSION_CXX_TYPE)
	s = cxx_sym;
      else
	s = sym;
      if (fnmatch (expr->pattern, s, 0) == 0)
	break;
    }

out_ret:
  if (cxx_sym != sym)
    free ((char *) cxx_sym);
  if (java_sym != sym)
    free ((char *) java_sym);
  return expr;
}