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
typedef  int /*<<< orphan*/  diagnostic_context ;

/* Variables and functions */
 scalar_t__ current_instantiation () ; 
 int /*<<< orphan*/  print_instantiation_full_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  problematic_instantiation_changed () ; 
 int /*<<< orphan*/  record_last_problematic_instantiation () ; 

__attribute__((used)) static void
maybe_print_instantiation_context (diagnostic_context *context)
{
  if (!problematic_instantiation_changed () || current_instantiation () == 0)
    return;

  record_last_problematic_instantiation ();
  print_instantiation_full_context (context);
}