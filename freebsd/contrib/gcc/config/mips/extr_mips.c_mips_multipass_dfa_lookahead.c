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
 scalar_t__ TUNE_SB1 ; 

__attribute__((used)) static int
mips_multipass_dfa_lookahead (void)
{
  /* Can schedule up to 4 of the 6 function units in any one cycle.  */
  if (TUNE_SB1)
    return 4;

  return 0;
}