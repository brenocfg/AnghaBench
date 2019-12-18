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
 int /*<<< orphan*/ * cp_parser_new () ; 
 int cp_parser_translation_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dk_no_check ; 
 int /*<<< orphan*/  dk_no_deferred ; 
 scalar_t__ flag_access_control ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorry (char*) ; 
 int /*<<< orphan*/ * the_parser ; 

void
c_parse_file (void)
{
  bool error_occurred;
  static bool already_called = false;

  if (already_called)
    {
      sorry ("inter-module optimizations not implemented for C++");
      return;
    }
  already_called = true;

  the_parser = cp_parser_new ();
  push_deferring_access_checks (flag_access_control
				? dk_no_deferred : dk_no_check);
  error_occurred = cp_parser_translation_unit (the_parser);
  the_parser = NULL;
}