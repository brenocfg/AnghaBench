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
 int TX39_CONF_HALT ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int read_c0_conf () ; 
 int /*<<< orphan*/  write_c0_conf (int) ; 

__attribute__((used)) static void r39xx_wait(void)
{
	local_irq_disable();
	if (!need_resched())
		write_c0_conf(read_c0_conf() | TX39_CONF_HALT);
	local_irq_enable();
}