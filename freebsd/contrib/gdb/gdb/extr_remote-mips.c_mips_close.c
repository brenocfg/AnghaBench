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
 int /*<<< orphan*/  close_ports () ; 
 int /*<<< orphan*/  mips_exit_debug () ; 
 scalar_t__ mips_is_open ; 

__attribute__((used)) static void
mips_close (int quitting)
{
  if (mips_is_open)
    {
      /* Get the board out of remote debugging mode.  */
      (void) mips_exit_debug ();

      close_ports ();
    }
}