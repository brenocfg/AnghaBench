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
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  rbtx4939_reseten_addr ; 
 int /*<<< orphan*/  rbtx4939_softreset_addr ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbtx4939_machine_restart(char *command)
{
	local_irq_disable();
	writeb(1, rbtx4939_reseten_addr);
	writeb(1, rbtx4939_softreset_addr);
	while (1)
		;
}