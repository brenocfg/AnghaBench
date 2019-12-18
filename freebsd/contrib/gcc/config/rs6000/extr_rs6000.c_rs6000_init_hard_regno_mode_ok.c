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
 int FIRST_PSEUDO_REGISTER ; 
 int NUM_MACHINE_MODES ; 
 scalar_t__ rs6000_hard_regno_mode_ok (int,int) ; 
 int** rs6000_hard_regno_mode_ok_p ; 

__attribute__((used)) static void
rs6000_init_hard_regno_mode_ok (void)
{
  int r, m;

  for (r = 0; r < FIRST_PSEUDO_REGISTER; ++r)
    for (m = 0; m < NUM_MACHINE_MODES; ++m)
      if (rs6000_hard_regno_mode_ok (r, m))
	rs6000_hard_regno_mode_ok_p[m][r] = true;
}