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
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  remove_breakpoints () ; 
 scalar_t__ sr_get_debug () ; 

__attribute__((used)) static void
gdbsim_mourn_inferior (void)
{
  if (sr_get_debug ())
    printf_filtered ("gdbsim_mourn_inferior:\n");

  remove_breakpoints ();
  generic_mourn_inferior ();
}