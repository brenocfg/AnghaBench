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
 scalar_t__ pluspresent ; 

int
mep_flush_pending_output (void)
{
  if (mode == VLIW)
    {
      mep_process_saved_insns ();
      pluspresent = 0;
    }

  return 1; 
}