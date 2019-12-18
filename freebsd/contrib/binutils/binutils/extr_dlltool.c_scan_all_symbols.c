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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HAS_SYMS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 long bfd_read_minisymbols (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,unsigned int*) ; 
 long filter_symbols (int /*<<< orphan*/ *,void*,long,unsigned int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_filtered_symbols (int /*<<< orphan*/ *,void*,long,unsigned int) ; 

__attribute__((used)) static void
scan_all_symbols (bfd *abfd)
{
  long symcount;
  void *minisyms;
  unsigned int size;

  /* Ignore bfds with an import descriptor table.  We assume that any
     such BFD contains symbols which are exported from another DLL,
     and we don't want to reexport them from here.  */
  if (bfd_get_section_by_name (abfd, ".idata$4"))
    return;

  if (! (bfd_get_file_flags (abfd) & HAS_SYMS))
    {
      /* xgettext:c-format */
      non_fatal (_("%s: no symbols"), bfd_get_filename (abfd));
      return;
    }

  symcount = bfd_read_minisymbols (abfd, FALSE, &minisyms, &size);
  if (symcount < 0)
    bfd_fatal (bfd_get_filename (abfd));

  if (symcount == 0)
    {
      /* xgettext:c-format */
      non_fatal (_("%s: no symbols"), bfd_get_filename (abfd));
      return;
    }

  /* Discard the symbols we don't want to export.  It's OK to do this
     in place; we'll free the storage anyway.  */

  symcount = filter_symbols (abfd, minisyms, symcount, size);
  scan_filtered_symbols (abfd, minisyms, symcount, size);

  free (minisyms);
}