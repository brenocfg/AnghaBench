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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_read_minisymbols (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,unsigned int*) ; 
 int /*<<< orphan*/  syms ; 

__attribute__((used)) static void
slurp_symtab (bfd *abfd)
{
  long symcount;
  unsigned int size;

  if ((bfd_get_file_flags (abfd) & HAS_SYMS) == 0)
    return;

  symcount = bfd_read_minisymbols (abfd, FALSE, (void *) &syms, &size);
  if (symcount == 0)
    symcount = bfd_read_minisymbols (abfd, TRUE /* dynamic */, (void *) &syms, &size);

  if (symcount < 0)
    bfd_fatal (bfd_get_filename (abfd));
}