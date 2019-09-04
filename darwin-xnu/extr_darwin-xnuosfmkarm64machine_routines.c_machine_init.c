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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clock_config () ; 
 scalar_t__ debug_enabled ; 
 int /*<<< orphan*/  debug_log_init () ; 
 int /*<<< orphan*/  is_clock_configured ; 
 int /*<<< orphan*/  pmap_map_globals () ; 

void
machine_init(void)
{
	debug_log_init();
	clock_config();
	is_clock_configured = TRUE;
	if (debug_enabled)
		pmap_map_globals();
}