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
 int /*<<< orphan*/  finish_alt_states () ; 
 int /*<<< orphan*/ * first_free_state ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_table ; 
 scalar_t__ units_array ; 

__attribute__((used)) static void
finish_states (void)
{
  free (units_array);
  units_array = 0;
  htab_delete (state_table);
  first_free_state = NULL;
  finish_alt_states ();
}