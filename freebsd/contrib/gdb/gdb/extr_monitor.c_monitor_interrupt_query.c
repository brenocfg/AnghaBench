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
 int /*<<< orphan*/  RETURN_QUIT ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  throw_exception (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
monitor_interrupt_query (void)
{
  target_terminal_ours ();

  if (query ("Interrupted while waiting for the program.\n\
Give up (and stop debugging it)? "))
    {
      target_mourn_inferior ();
      throw_exception (RETURN_QUIT);
    }

  target_terminal_inferior ();
}