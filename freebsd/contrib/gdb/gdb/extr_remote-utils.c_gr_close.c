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
 int /*<<< orphan*/  gr_clear_all_breakpoints () ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_get_desc () ; 
 scalar_t__ sr_is_open () ; 
 int /*<<< orphan*/  sr_set_desc (int /*<<< orphan*/ *) ; 

void
gr_close (int quitting)
{
  gr_clear_all_breakpoints ();

  if (sr_is_open ())
    {
      serial_close (sr_get_desc ());
      sr_set_desc (NULL);
    }

  return;
}