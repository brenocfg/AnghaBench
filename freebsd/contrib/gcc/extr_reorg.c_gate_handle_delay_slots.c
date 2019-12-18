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
 int flag_delayed_branch ; 

__attribute__((used)) static bool
gate_handle_delay_slots (void)
{
#ifdef DELAY_SLOTS
  return flag_delayed_branch;
#else 
  return 0;
#endif
}