#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct size_sym {scalar_t__ size; void const* minisym; } ;
struct TYPE_10__ {scalar_t__ st_size; } ;
struct TYPE_11__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_12__ {scalar_t__ value; } ;
typedef  TYPE_3__ asymbol ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section (TYPE_3__*) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_is_com_section (int /*<<< orphan*/ *) ; 
 TYPE_3__* bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,TYPE_3__*) ; 
 scalar_t__ bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  qsort (void*,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_forward1 ; 
 int /*<<< orphan*/  size_forward2 ; 
 TYPE_3__* sort_x ; 
 TYPE_3__* sort_y ; 
 scalar_t__ valueof (TYPE_3__*) ; 
 struct size_sym* xmalloc (long) ; 

__attribute__((used)) static long
sort_symbols_by_size (bfd *abfd, bfd_boolean dynamic, void *minisyms,
		      long symcount, unsigned int size,
		      struct size_sym **symsizesp)
{
  struct size_sym *symsizes;
  bfd_byte *from, *fromend;
  asymbol *sym = NULL;
  asymbol *store_sym, *store_next;

  qsort (minisyms, symcount, size, size_forward1);

  /* We are going to return a special set of symbols and sizes to
     print.  */
  symsizes = xmalloc (symcount * sizeof (struct size_sym));
  *symsizesp = symsizes;

  /* Note that filter_symbols has already removed all absolute and
     undefined symbols.  Here we remove all symbols whose size winds
     up as zero.  */
  from = (bfd_byte *) minisyms;
  fromend = from + symcount * size;

  store_sym = sort_x;
  store_next = sort_y;

  if (from < fromend)
    {
      sym = bfd_minisymbol_to_symbol (abfd, dynamic, (const void *) from,
				      store_sym);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));
    }

  for (; from < fromend; from += size)
    {
      asymbol *next;
      asection *sec;
      bfd_vma sz;
      asymbol *temp;

      if (from + size < fromend)
	{
	  next = bfd_minisymbol_to_symbol (abfd,
					   dynamic,
					   (const void *) (from + size),
					   store_next);
	  if (next == NULL)
	    bfd_fatal (bfd_get_filename (abfd));
	}
      else
	next = NULL;

      sec = bfd_get_section (sym);

      if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
	sz = ((elf_symbol_type *) sym)->internal_elf_sym.st_size;
      else if (bfd_is_com_section (sec))
	sz = sym->value;
      else
	{
	  if (from + size < fromend
	      && sec == bfd_get_section (next))
	    sz = valueof (next) - valueof (sym);
	  else
	    sz = (bfd_get_section_vma (abfd, sec)
		  + bfd_section_size (abfd, sec)
		  - valueof (sym));
	}

      if (sz != 0)
	{
	  symsizes->minisym = (const void *) from;
	  symsizes->size = sz;
	  ++symsizes;
	}

      sym = next;

      temp = store_sym;
      store_sym = store_next;
      store_next = temp;
    }

  symcount = symsizes - *symsizesp;

  /* We must now sort again by size.  */
  qsort ((void *) *symsizesp, symcount, sizeof (struct size_sym), size_forward2);

  return symcount;
}