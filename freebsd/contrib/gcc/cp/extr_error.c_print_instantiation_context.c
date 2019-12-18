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
 int /*<<< orphan*/  current_instantiation () ; 
 int /*<<< orphan*/  diagnostic_flush_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_dc ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  print_instantiation_partial_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_instantiation_context (void)
{
  print_instantiation_partial_context
    (global_dc, current_instantiation (), input_location);
  diagnostic_flush_buffer (global_dc);
}