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
 int /*<<< orphan*/  REG_DBG_PRINT (char*) ; 
 int /*<<< orphan*/  restore_regulatory_settings (int) ; 

void regulatory_hint_disconnect(void)
{
	REG_DBG_PRINT("All devices are disconnected, going to restore regulatory settings\n");
	restore_regulatory_settings(false);
}