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
 int /*<<< orphan*/  dbr_schedule (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 

__attribute__((used)) static unsigned int
rest_of_handle_delay_slots (void)
{
#ifdef DELAY_SLOTS
  dbr_schedule (get_insns ());
#endif
  return 0;
}