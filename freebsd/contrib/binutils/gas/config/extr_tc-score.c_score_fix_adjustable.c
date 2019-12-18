#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fx_r_type; int /*<<< orphan*/ * fx_addsy; } ;
typedef  TYPE_1__ fixS ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_VTABLE_ENTRY ; 
 scalar_t__ BFD_RELOC_VTABLE_INHERIT ; 
 scalar_t__ OUTPUT_FLAVOR ; 
 scalar_t__ S_IS_EXTERNAL (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_WEAK (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_elf_flavour ; 

bfd_boolean
score_fix_adjustable (fixS * fixP)
{
  if (fixP->fx_addsy == NULL)
    {
      return 1;
    }
  else if (OUTPUT_FLAVOR == bfd_target_elf_flavour
      && (S_IS_EXTERNAL (fixP->fx_addsy) || S_IS_WEAK (fixP->fx_addsy)))
    {
      return 0;
    }
  else if (fixP->fx_r_type == BFD_RELOC_VTABLE_INHERIT
      || fixP->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    {
      return 0;
    }

  return 1;
}