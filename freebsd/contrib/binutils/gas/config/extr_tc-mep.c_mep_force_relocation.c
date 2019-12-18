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
struct TYPE_3__ {scalar_t__ fx_r_type; int /*<<< orphan*/  fx_pcrel; int /*<<< orphan*/  fx_addsy; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_VTABLE_ENTRY ; 
 scalar_t__ BFD_RELOC_VTABLE_INHERIT ; 
 int S_FORCE_RELOC (int /*<<< orphan*/ ,int) ; 

int
mep_force_relocation (fixS *fixp)
{
  if (   fixp->fx_r_type == BFD_RELOC_VTABLE_INHERIT
	 || fixp->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    return 1;

  /* Allow branches to global symbols to be resolved at assembly time.
     This is consistent with way relaxable branches are handled, since
     branches to both global and local symbols are relaxed.  It also
     corresponds to the assumptions made in md_pcrel_from_section.  */
  return S_FORCE_RELOC (fixp->fx_addsy, !fixp->fx_pcrel);
}