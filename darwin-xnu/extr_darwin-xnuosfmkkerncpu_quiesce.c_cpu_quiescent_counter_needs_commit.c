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
typedef  int checkin_mask_t ;

/* Variables and functions */
 int CPU_CHECKIN_MASK ; 
 int CPU_EXPECTED_MASK ; 

__attribute__((used)) static bool
cpu_quiescent_counter_needs_commit(checkin_mask_t state)
{
	return (state & CPU_CHECKIN_MASK) == ((state & CPU_EXPECTED_MASK) >> 1);
}