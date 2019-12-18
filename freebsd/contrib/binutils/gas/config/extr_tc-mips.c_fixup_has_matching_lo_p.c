#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fx_addsy; scalar_t__ fx_offset; TYPE_1__* fx_next; } ;
typedef  TYPE_2__ fixS ;
typedef  int bfd_boolean ;
struct TYPE_4__ {scalar_t__ fx_r_type; scalar_t__ fx_addsy; scalar_t__ fx_offset; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_LO16 ; 
 scalar_t__ BFD_RELOC_MIPS16_LO16 ; 

__attribute__((used)) static inline bfd_boolean
fixup_has_matching_lo_p (fixS *fixp)
{
  return (fixp->fx_next != NULL
	  && (fixp->fx_next->fx_r_type == BFD_RELOC_LO16
	     || fixp->fx_next->fx_r_type == BFD_RELOC_MIPS16_LO16)
	  && fixp->fx_addsy == fixp->fx_next->fx_addsy
	  && fixp->fx_offset == fixp->fx_next->fx_offset);
}