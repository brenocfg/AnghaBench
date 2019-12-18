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
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  case_mode ; 
 int /*<<< orphan*/  case_mode_auto ; 
 int /*<<< orphan*/  case_mode_manual ; 
 int /*<<< orphan*/  case_sensitive ; 
 int /*<<< orphan*/  case_sensitive_off ; 
 int /*<<< orphan*/  case_sensitive_on ; 
 int /*<<< orphan*/  case_sensitivity ; 
 int /*<<< orphan*/  set_case_str () ; 
 int /*<<< orphan*/  set_type_range_case () ; 
 int /*<<< orphan*/  show_case_command (char*,int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_case_command (char *ignore, int from_tty)
{
   if (DEPRECATED_STREQ (case_sensitive, "on"))
   {
      case_sensitivity = case_sensitive_on;
      case_mode = case_mode_manual;
   }
   else if (DEPRECATED_STREQ (case_sensitive, "off"))
   {
      case_sensitivity = case_sensitive_off;
      case_mode = case_mode_manual;
   }
   else if (DEPRECATED_STREQ (case_sensitive, "auto"))
   {
      case_mode = case_mode_auto;
      set_type_range_case ();
      /* Avoid hitting the set_case_str call below.  We
         did it in set_type_range_case. */
      return;
   }
   else
   {
      warning ("Unrecognized case-sensitive setting: \"%s\"", case_sensitive);
   }
   set_case_str();
   show_case_command ((char *) NULL, from_tty);
}