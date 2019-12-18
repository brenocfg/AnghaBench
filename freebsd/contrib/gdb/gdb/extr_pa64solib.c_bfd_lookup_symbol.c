#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {TYPE_1__* section; scalar_t__ value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_5__ {scalar_t__ vma; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 unsigned int bfd_canonicalize_symtab (int /*<<< orphan*/ *,TYPE_2__**) ; 
 unsigned int bfd_get_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static CORE_ADDR
bfd_lookup_symbol (bfd *abfd, char *symname)
{
  unsigned int storage_needed;
  asymbol *sym;
  asymbol **symbol_table;
  unsigned int number_of_symbols;
  unsigned int i;
  struct cleanup *back_to;
  CORE_ADDR symaddr = 0;

  storage_needed = bfd_get_symtab_upper_bound (abfd);

  if (storage_needed > 0)
    {
      symbol_table = (asymbol **) xmalloc (storage_needed);
      back_to = make_cleanup (xfree, symbol_table);
      number_of_symbols = bfd_canonicalize_symtab (abfd, symbol_table);

      for (i = 0; i < number_of_symbols; i++)
	{
	  sym = *symbol_table++;
	  if (strcmp (sym->name, symname) == 0)
	    {
	      /* Bfd symbols are section relative. */
	      symaddr = sym->value + sym->section->vma;
	      break;
	    }
	}
      do_cleanups (back_to);
    }
  return (symaddr);
}