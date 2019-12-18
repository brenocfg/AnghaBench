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
 int /*<<< orphan*/  SYS_RESTART ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtas_flash_term_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

void rtas_restart(char *cmd)
{
	if (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_RESTART);
	printk("RTAS system-reboot returned %d\n",
	       rtas_call(rtas_token("system-reboot"), 0, 1, NULL));
	for (;;);
}