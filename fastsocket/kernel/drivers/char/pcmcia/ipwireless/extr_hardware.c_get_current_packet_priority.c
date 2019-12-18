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
struct ipw_hardware {scalar_t__ initializing; scalar_t__ to_setup; } ;

/* Variables and functions */
 int NL_NUM_OF_PRIORITIES ; 
 int PRIO_SETUP ; 

__attribute__((used)) static int get_current_packet_priority(struct ipw_hardware *hw)
{
	/*
	 * If we're initializing, don't send anything of higher priority than
	 * PRIO_SETUP.  The network layer therefore need not care about
	 * hardware initialization - any of its stuff will simply be queued
	 * until setup is complete.
	 */
	return (hw->to_setup || hw->initializing
			? PRIO_SETUP + 1 : NL_NUM_OF_PRIORITIES);
}