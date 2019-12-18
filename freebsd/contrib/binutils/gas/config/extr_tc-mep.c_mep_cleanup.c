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
 scalar_t__ VLIW ; 
 int /*<<< orphan*/  mep_process_saved_insns () ; 
 scalar_t__ mode ; 

void
mep_cleanup (void)
{
  /* Take care of any insns left to be parallelized when the file ends.
     This is mainly here to handle the case where the file ends with an
     insn preceeded by a + or the file ends unexpectedly.  */
  if (mode == VLIW)
    mep_process_saved_insns ();
}