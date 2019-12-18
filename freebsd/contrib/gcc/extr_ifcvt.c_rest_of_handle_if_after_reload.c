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
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 scalar_t__ flag_crossjumping ; 
 scalar_t__ flag_if_conversion2 ; 
 int /*<<< orphan*/  if_convert (int) ; 

__attribute__((used)) static unsigned int
rest_of_handle_if_after_reload (void)
{
  /* Last attempt to optimize CFG, as scheduling, peepholing and insn
     splitting possibly introduced more crossjumping opportunities.  */
  cleanup_cfg (CLEANUP_EXPENSIVE
               | CLEANUP_UPDATE_LIFE
               | (flag_crossjumping ? CLEANUP_CROSSJUMP : 0));
  if (flag_if_conversion2)
    if_convert (1);
  return 0;
}