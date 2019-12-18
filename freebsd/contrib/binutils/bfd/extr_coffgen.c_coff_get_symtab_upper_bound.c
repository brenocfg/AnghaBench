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

/* Variables and functions */
 int /*<<< orphan*/  bfd_coff_slurp_symbol_table (int /*<<< orphan*/ *) ; 
 int bfd_get_symcount (int /*<<< orphan*/ *) ; 

long
coff_get_symtab_upper_bound (bfd *abfd)
{
  if (!bfd_coff_slurp_symbol_table (abfd))
    return -1;

  return (bfd_get_symcount (abfd) + 1) * (sizeof (coff_symbol_type *));
}