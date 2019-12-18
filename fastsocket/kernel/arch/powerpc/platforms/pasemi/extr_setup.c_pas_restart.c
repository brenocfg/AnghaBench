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
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  reset_reg ; 
 int /*<<< orphan*/  smp_send_stop () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pas_restart(char *cmd)
{
	/* Need to put others cpu in hold loop so they're not sleeping */
	smp_send_stop();
	udelay(10000);
	printk("Restarting...\n");
	while (1)
		out_le32(reset_reg, 0x6000000);
}