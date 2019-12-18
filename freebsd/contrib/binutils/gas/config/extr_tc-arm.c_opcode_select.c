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
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_ARM ; 
 int /*<<< orphan*/  MAP_THUMB ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_ext_v1 ; 
 int /*<<< orphan*/  arm_ext_v4t ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  frag_align (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  need_pass_2 ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  record_alignment (int /*<<< orphan*/ ,int) ; 
 int thumb_mode ; 

__attribute__((used)) static void
opcode_select (int width)
{
  switch (width)
    {
    case 16:
      if (! thumb_mode)
	{
	  if (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v4t))
	    as_bad (_("selected processor does not support THUMB opcodes"));

	  thumb_mode = 1;
	  /* No need to force the alignment, since we will have been
	     coming from ARM mode, which is word-aligned.  */
	  record_alignment (now_seg, 1);
	}
      mapping_state (MAP_THUMB);
      break;

    case 32:
      if (thumb_mode)
	{
	  if (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v1))
	    as_bad (_("selected processor does not support ARM opcodes"));

	  thumb_mode = 0;

	  if (!need_pass_2)
	    frag_align (2, 0, 0);

	  record_alignment (now_seg, 1);
	}
      mapping_state (MAP_ARM);
      break;

    default:
      as_bad (_("invalid instruction size selected (%d)"), width);
    }
}