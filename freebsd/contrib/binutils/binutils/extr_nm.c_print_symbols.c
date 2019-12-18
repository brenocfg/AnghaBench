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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_minisymbol_to_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_symbols (bfd *abfd, bfd_boolean dynamic, void *minisyms, long symcount,
	       unsigned int size, bfd *archive_bfd)
{
  asymbol *store;
  bfd_byte *from, *fromend;

  store = bfd_make_empty_symbol (abfd);
  if (store == NULL)
    bfd_fatal (bfd_get_filename (abfd));

  from = (bfd_byte *) minisyms;
  fromend = from + symcount * size;
  for (; from < fromend; from += size)
    {
      asymbol *sym;

      sym = bfd_minisymbol_to_symbol (abfd, dynamic, from, store);
      if (sym == NULL)
	bfd_fatal (bfd_get_filename (abfd));

      print_symbol (abfd, sym, (bfd_vma) 0, archive_bfd);
    }
}