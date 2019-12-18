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
 int /*<<< orphan*/  AT91_EMAC_SR ; 
 int AT91_EMAC_SR_IDLE ; 
 int at91_emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int jiffies ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static inline void at91_phy_wait(void) {
	unsigned long timeout = jiffies + 2;

	while (!(at91_emac_read(AT91_EMAC_SR) & AT91_EMAC_SR_IDLE)) {
		if (time_after(jiffies, timeout)) {
			printk("at91_ether: MIO timeout\n");
			break;
		}
		cpu_relax();
	}
}