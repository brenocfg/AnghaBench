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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int pc_in_dummy_frame (int /*<<< orphan*/ ) ; 

int
generic_pc_in_call_dummy (CORE_ADDR pc, CORE_ADDR sp, CORE_ADDR fp)
{
  return pc_in_dummy_frame (pc);
}