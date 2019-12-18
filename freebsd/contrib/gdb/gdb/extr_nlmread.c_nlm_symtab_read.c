#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct objfile {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum minimal_symbol_type { ____Placeholder_minimal_symbol_type } minimal_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_4__* section; scalar_t__ value; } ;
typedef  TYPE_1__ asymbol ;
struct TYPE_6__ {int flags; scalar_t__ vma; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int SEC_CODE ; 
 int SEC_DATA ; 
 TYPE_4__ bfd_abs_section ; 
 long bfd_canonicalize_symtab (int /*<<< orphan*/ *,TYPE_1__**) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_get_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int mst_data ; 
 int mst_text ; 
 int mst_unknown ; 
 int /*<<< orphan*/  prim_record_minimal_symbol (int /*<<< orphan*/ ,scalar_t__,int,struct objfile*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (long) ; 

__attribute__((used)) static void
nlm_symtab_read (bfd *abfd, CORE_ADDR addr, struct objfile *objfile)
{
  long storage_needed;
  asymbol *sym;
  asymbol **symbol_table;
  long number_of_symbols;
  long i;
  struct cleanup *back_to;
  CORE_ADDR symaddr;
  enum minimal_symbol_type ms_type;

  storage_needed = bfd_get_symtab_upper_bound (abfd);
  if (storage_needed < 0)
    error ("Can't read symbols from %s: %s", bfd_get_filename (abfd),
	   bfd_errmsg (bfd_get_error ()));
  if (storage_needed > 0)
    {
      symbol_table = (asymbol **) xmalloc (storage_needed);
      back_to = make_cleanup (xfree, symbol_table);
      number_of_symbols = bfd_canonicalize_symtab (abfd, symbol_table);
      if (number_of_symbols < 0)
	error ("Can't read symbols from %s: %s", bfd_get_filename (abfd),
	       bfd_errmsg (bfd_get_error ()));

      for (i = 0; i < number_of_symbols; i++)
	{
	  sym = symbol_table[i];
	  if ( /*sym -> flags & BSF_GLOBAL */ 1)
	    {
	      /* Bfd symbols are section relative. */
	      symaddr = sym->value + sym->section->vma;
	      /* Relocate all non-absolute symbols by base address.  */
	      if (sym->section != &bfd_abs_section)
		symaddr += addr;

	      /* For non-absolute symbols, use the type of the section
	         they are relative to, to intuit text/data.  BFD provides
	         no way of figuring this out for absolute symbols. */
	      if (sym->section->flags & SEC_CODE)
		ms_type = mst_text;
	      else if (sym->section->flags & SEC_DATA)
		ms_type = mst_data;
	      else
		ms_type = mst_unknown;

	      prim_record_minimal_symbol (sym->name, symaddr, ms_type,
					  objfile);
	    }
	}
      do_cleanups (back_to);
    }
}