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
 int /*<<< orphan*/  range ; 
 int /*<<< orphan*/  range_check ; 
 int /*<<< orphan*/  range_check_off ; 
 int /*<<< orphan*/  range_check_on ; 
 int /*<<< orphan*/  range_check_warn ; 
 int /*<<< orphan*/  range_mode ; 
 int /*<<< orphan*/  range_mode_auto ; 
 int /*<<< orphan*/  range_mode_manual ; 
 int /*<<< orphan*/  set_range_str () ; 
 int /*<<< orphan*/  set_type_range_case () ; 
 int /*<<< orphan*/  show_range_command (char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_range_command (char *ignore, int from_tty)
{
  if (strcmp (range, "on") == 0)
    {
      range_check = range_check_on;
      range_mode = range_mode_manual;
    }
  else if (strcmp (range, "warn") == 0)
    {
      range_check = range_check_warn;
      range_mode = range_mode_manual;
    }
  else if (strcmp (range, "off") == 0)
    {
      range_check = range_check_off;
      range_mode = range_mode_manual;
    }
  else if (strcmp (range, "auto") == 0)
    {
      range_mode = range_mode_auto;
      set_type_range_case ();
      /* Avoid hitting the set_range_str call below.  We
         did it in set_type_range_case. */
      return;
    }
  else
    {
      warning ("Unrecognized range check setting: \"%s\"", range);
    }
  set_range_str ();
  show_range_command ((char *) 0, from_tty);
}