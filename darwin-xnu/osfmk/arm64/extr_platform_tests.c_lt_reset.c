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
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 scalar_t__ lt_counter ; 
 scalar_t__ lt_cpu_bind_id ; 
 scalar_t__ lt_done_threads ; 
 scalar_t__ lt_max_holders ; 
 scalar_t__ lt_max_upgrade_holders ; 
 scalar_t__ lt_num_holders ; 
 scalar_t__ lt_target_done_threads ; 
 scalar_t__ lt_upgrade_holders ; 

__attribute__((used)) static void
lt_reset()
{
	lt_counter = 0;
	lt_max_holders = 0;
	lt_num_holders = 0;
	lt_max_upgrade_holders = 0;
	lt_upgrade_holders = 0;
	lt_done_threads = 0;
	lt_target_done_threads = 0;
	lt_cpu_bind_id = 0;

	OSMemoryBarrier();
}