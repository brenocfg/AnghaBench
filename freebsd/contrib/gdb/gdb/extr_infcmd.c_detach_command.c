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
 int /*<<< orphan*/  SOLIB_RESTART () ; 
 int /*<<< orphan*/  detach_hook () ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  target_detach (char*,int) ; 

__attribute__((used)) static void
detach_command (char *args, int from_tty)
{
  dont_repeat ();		/* Not for the faint of heart */
  target_detach (args, from_tty);
#if defined(SOLIB_RESTART)
  SOLIB_RESTART ();
#endif
  if (detach_hook)
    detach_hook ();
}