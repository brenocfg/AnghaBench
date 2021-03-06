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
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  detect_strict_aliasing_named () ; 
 scalar_t__ flag_strict_aliasing ; 
 int /*<<< orphan*/  maybe_free_reference_table () ; 
 int /*<<< orphan*/  processed_func_p (int /*<<< orphan*/ ) ; 
 int warn_strict_aliasing ; 

void
strict_aliasing_warning_backend (void)
{
  if (!(flag_strict_aliasing
        && warn_strict_aliasing == 3
        && !processed_func_p (current_function_decl)))
    return;

  detect_strict_aliasing_named ();
  maybe_free_reference_table ();
}