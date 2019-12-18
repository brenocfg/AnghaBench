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
struct TYPE_4__ {scalar_t__ fx_r_type; int /*<<< orphan*/  fx_addsy; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_HI16_S ; 
 scalar_t__ BFD_RELOC_LO16 ; 
 scalar_t__ BFD_RELOC_MIPS_SUB ; 
 scalar_t__ HAVE_NEWABI ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_abs_section_ptr ; 
 scalar_t__ generic_force_reloc (TYPE_1__*) ; 

int
mips_force_relocation (fixS *fixp)
{
  if (generic_force_reloc (fixp))
    return 1;

  if (HAVE_NEWABI
      && S_GET_SEGMENT (fixp->fx_addsy) == bfd_abs_section_ptr
      && (fixp->fx_r_type == BFD_RELOC_MIPS_SUB
	  || fixp->fx_r_type == BFD_RELOC_HI16_S
	  || fixp->fx_r_type == BFD_RELOC_LO16))
    return 1;

  return 0;
}