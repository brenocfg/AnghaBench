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
 int /*<<< orphan*/  set_type_range_case () ; 
 int /*<<< orphan*/  set_type_str () ; 
 int /*<<< orphan*/  show_type_command (char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  type_check ; 
 int /*<<< orphan*/  type_check_off ; 
 int /*<<< orphan*/  type_check_on ; 
 int /*<<< orphan*/  type_check_warn ; 
 int /*<<< orphan*/  type_mode ; 
 int /*<<< orphan*/  type_mode_auto ; 
 int /*<<< orphan*/  type_mode_manual ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_type_command (char *ignore, int from_tty)
{
  if (strcmp (type, "on") == 0)
    {
      type_check = type_check_on;
      type_mode = type_mode_manual;
    }
  else if (strcmp (type, "warn") == 0)
    {
      type_check = type_check_warn;
      type_mode = type_mode_manual;
    }
  else if (strcmp (type, "off") == 0)
    {
      type_check = type_check_off;
      type_mode = type_mode_manual;
    }
  else if (strcmp (type, "auto") == 0)
    {
      type_mode = type_mode_auto;
      set_type_range_case ();
      /* Avoid hitting the set_type_str call below.  We
         did it in set_type_range_case. */
      return;
    }
  else
    {
      warning ("Unrecognized type check setting: \"%s\"", type);
    }
  set_type_str ();
  show_type_command ((char *) NULL, from_tty);
}