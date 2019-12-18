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
 int /*<<< orphan*/  init_reg_autoinc () ; 
 int /*<<< orphan*/  init_reg_sets_1 () ; 

void
init_regs (void)
{
  /* This finishes what was started by init_reg_sets, but couldn't be done
     until after register usage was specified.  */
  init_reg_sets_1 ();

  init_reg_autoinc ();
}