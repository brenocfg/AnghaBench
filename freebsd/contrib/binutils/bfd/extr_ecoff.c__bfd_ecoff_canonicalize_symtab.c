#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ecoff_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_2__ {int /*<<< orphan*/ * canonical_symbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_ecoff_slurp_symbol_table (int /*<<< orphan*/ *) ; 
 long bfd_get_symcount (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecoff_data (int /*<<< orphan*/ *) ; 

long
_bfd_ecoff_canonicalize_symtab (bfd *abfd, asymbol **alocation)
{
  unsigned int counter = 0;
  ecoff_symbol_type *symbase;
  ecoff_symbol_type **location = (ecoff_symbol_type **) alocation;

  if (! _bfd_ecoff_slurp_symbol_table (abfd))
    return -1;
  if (bfd_get_symcount (abfd) == 0)
    return 0;

  symbase = ecoff_data (abfd)->canonical_symbols;
  while (counter < bfd_get_symcount (abfd))
    {
      *(location++) = symbase++;
      counter++;
    }
  *location++ = NULL;
  return bfd_get_symcount (abfd);
}