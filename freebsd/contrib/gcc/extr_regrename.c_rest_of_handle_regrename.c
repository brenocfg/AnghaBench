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
 int /*<<< orphan*/  copyprop_hardreg_forward () ; 
 scalar_t__ flag_cprop_registers ; 
 scalar_t__ flag_rename_registers ; 
 int /*<<< orphan*/  regrename_optimize () ; 

__attribute__((used)) static unsigned int
rest_of_handle_regrename (void)
{
  if (flag_rename_registers)
    regrename_optimize ();
  if (flag_cprop_registers)
    copyprop_hardreg_forward ();
  return 0;
}