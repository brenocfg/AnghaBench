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
 int ENOMEM ; 
 int /*<<< orphan*/ * claw_dbf_setup ; 
 int /*<<< orphan*/ * claw_dbf_trace ; 
 int /*<<< orphan*/  claw_unregister_debug_facility () ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 int /*<<< orphan*/ * debug_register (char*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
claw_register_debug_facility(void)
{
	claw_dbf_setup = debug_register("claw_setup", 2, 1, 8);
	claw_dbf_trace = debug_register("claw_trace", 2, 2, 8);
	if (claw_dbf_setup == NULL || claw_dbf_trace == NULL) {
		claw_unregister_debug_facility();
		return -ENOMEM;
	}
	debug_register_view(claw_dbf_setup, &debug_hex_ascii_view);
	debug_set_level(claw_dbf_setup, 2);
	debug_register_view(claw_dbf_trace, &debug_hex_ascii_view);
	debug_set_level(claw_dbf_trace, 2);
	return 0;
}