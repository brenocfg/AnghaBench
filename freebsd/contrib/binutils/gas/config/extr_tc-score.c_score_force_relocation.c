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
struct fix {scalar_t__ fx_r_type; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_SCORE16_BRANCH ; 
 scalar_t__ BFD_RELOC_SCORE16_JMP ; 
 scalar_t__ BFD_RELOC_SCORE_BRANCH ; 
 scalar_t__ BFD_RELOC_SCORE_JMP ; 
 scalar_t__ BFD_RELOC_VTABLE_ENTRY ; 
 scalar_t__ BFD_RELOC_VTABLE_INHERIT ; 

int
score_force_relocation (struct fix *fixp)
{
  int retval = 0;

  if (fixp->fx_r_type == BFD_RELOC_VTABLE_INHERIT
      || fixp->fx_r_type == BFD_RELOC_VTABLE_ENTRY
      || fixp->fx_r_type == BFD_RELOC_SCORE_JMP
      || fixp->fx_r_type == BFD_RELOC_SCORE_BRANCH
      || fixp->fx_r_type == BFD_RELOC_SCORE16_JMP
      || fixp->fx_r_type == BFD_RELOC_SCORE16_BRANCH)
    {
      retval = 1;
    }

  return retval;
}