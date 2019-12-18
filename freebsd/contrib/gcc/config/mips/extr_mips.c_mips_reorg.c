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

/* Variables and functions */
 scalar_t__ TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ TARGET_VR4130_ALIGN ; 
 scalar_t__ TUNE_MIPS4130 ; 
 int /*<<< orphan*/  dbr_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  mips16_lay_out_constants () ; 
 int /*<<< orphan*/  mips_avoid_hazards () ; 
 scalar_t__ mips_flag_delayed_branch ; 
 int /*<<< orphan*/  vr4130_align_insns () ; 

__attribute__((used)) static void
mips_reorg (void)
{
  if (TARGET_MIPS16)
    mips16_lay_out_constants ();
  else if (TARGET_EXPLICIT_RELOCS)
    {
      if (mips_flag_delayed_branch)
	dbr_schedule (get_insns ());
      mips_avoid_hazards ();
      if (TUNE_MIPS4130 && TARGET_VR4130_ALIGN)
	vr4130_align_insns ();
    }
}