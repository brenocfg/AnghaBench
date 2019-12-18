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
 int /*<<< orphan*/  SYS_HALT ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtas_flash_term_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

void rtas_halt(void)
{
	if (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_HALT);
	/* allow power on only with power button press */
	printk("RTAS power-off returned %d\n",
	       rtas_call(rtas_token("power-off"), 2, 1, NULL, -1, -1));
	for (;;);
}