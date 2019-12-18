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
struct size_sym {scalar_t__ size; int /*<<< orphan*/  minisym; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 int /*<<< orphan*/  print_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_size_symbols (bfd *abfd, bfd_boolean dynamic,
		    struct size_sym *symsizes, long symcount,
		    bfd *archive_bfd)
{
  asymbol *store;
  struct size_sym *from, *fromend;

  store = bfd_make_empty_symbol (abfd);
  if (store == NULL)
    bfd_fatal (bfd_get_filename (abfd));

  from = symsizes;
  fromend = from + symcount;
  for (; from < fromend; from++)
    {
      asymbol *sym;
      bfd_vma ssize;

      sym = bfd_minisymbol_to_symbol (abfd, dynamic, from->minisym, store);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      /* For elf we have already computed the correct symbol size.  */
      if (bfd_get_flavour (abfd) == bfd_target_elf_flavour)
	ssize = from->size;
      else
	ssize = from->size - bfd_section_vma (abfd, bfd_get_section (sym));

      print_symbol (abfd, sym, ssize, archive_bfd);
    }
}