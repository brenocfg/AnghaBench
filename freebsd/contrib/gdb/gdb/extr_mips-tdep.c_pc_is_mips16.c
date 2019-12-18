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
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 scalar_t__ is_mips16_addr (int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 int msymbol_is_special (struct minimal_symbol*) ; 

__attribute__((used)) static int
pc_is_mips16 (bfd_vma memaddr)
{
  struct minimal_symbol *sym;

  /* If bit 0 of the address is set, assume this is a MIPS16 address. */
  if (is_mips16_addr (memaddr))
    return 1;

  /* A flag indicating that this is a MIPS16 function is stored by elfread.c in
     the high bit of the info field.  Use this to decide if the function is
     MIPS16 or normal MIPS.  */
  sym = lookup_minimal_symbol_by_pc (memaddr);
  if (sym)
    return msymbol_is_special (sym);
  else
    return 0;
}