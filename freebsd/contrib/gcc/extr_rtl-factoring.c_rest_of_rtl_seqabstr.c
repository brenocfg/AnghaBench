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
 int CLEANUP_CROSSJUMP ; 
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_UPDATE_LIFE ; 
 int PROP_DEATH_NOTES ; 
 int PROP_KILL_DEAD_CODE ; 
 int PROP_SCAN_DEAD_CODE ; 
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 scalar_t__ flag_crossjumping ; 
 int /*<<< orphan*/  life_analysis (int) ; 
 int /*<<< orphan*/  rtl_seqabstr () ; 

__attribute__((used)) static unsigned int
rest_of_rtl_seqabstr (void)
{
  life_analysis (PROP_DEATH_NOTES | PROP_SCAN_DEAD_CODE | PROP_KILL_DEAD_CODE);

  cleanup_cfg (CLEANUP_EXPENSIVE |
               CLEANUP_UPDATE_LIFE |
               (flag_crossjumping ? CLEANUP_CROSSJUMP : 0));

  /* Abstract out common insn sequences. */
  rtl_seqabstr ();
  return 0;
}