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
typedef  int /*<<< orphan*/  coff_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_coff_slurp_symbol_table (int /*<<< orphan*/ *) ; 
 long bfd_get_symcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obj_symbols (int /*<<< orphan*/ *) ; 

long
coff_canonicalize_symtab (bfd *abfd, asymbol **alocation)
{
  unsigned int counter;
  coff_symbol_type *symbase;
  coff_symbol_type **location = (coff_symbol_type **) alocation;

  if (!bfd_coff_slurp_symbol_table (abfd))
    return -1;

  symbase = obj_symbols (abfd);
  counter = bfd_get_symcount (abfd);
  while (counter-- > 0)
    *location++ = symbase++;

  *location = NULL;

  return bfd_get_symcount (abfd);
}