#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ieee_symbol_type ;
struct TYPE_4__ {int symcount; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  ieee_slurp_symbol_table (TYPE_1__*) ; 

__attribute__((used)) static long
ieee_get_symtab_upper_bound (bfd *abfd)
{
  if (! ieee_slurp_symbol_table (abfd))
    return -1;

  return (abfd->symcount != 0) ?
    (abfd->symcount + 1) * (sizeof (ieee_symbol_type *)) : 0;
}