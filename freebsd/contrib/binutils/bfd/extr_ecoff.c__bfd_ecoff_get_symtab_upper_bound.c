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
struct TYPE_2__ {int /*<<< orphan*/  debug_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_ecoff_slurp_symbolic_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bfd_get_symcount (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecoff_data (int /*<<< orphan*/ *) ; 

long
_bfd_ecoff_get_symtab_upper_bound (bfd *abfd)
{
  if (! _bfd_ecoff_slurp_symbolic_info (abfd, NULL,
					&ecoff_data (abfd)->debug_info))
    return -1;

  if (bfd_get_symcount (abfd) == 0)
    return 0;

  return (bfd_get_symcount (abfd) + 1) * (sizeof (ecoff_symbol_type *));
}