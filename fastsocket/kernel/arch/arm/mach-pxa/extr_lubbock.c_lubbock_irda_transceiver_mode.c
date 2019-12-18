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
struct device {int dummy; } ;

/* Variables and functions */
 int IR_FIRMODE ; 
 int IR_SIRMODE ; 
 int LUB_MISC_WR ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pxa2xx_transceiver_mode (struct device*,int) ; 

__attribute__((used)) static void lubbock_irda_transceiver_mode(struct device *dev, int mode)
{
	unsigned long flags;

	local_irq_save(flags);
	if (mode & IR_SIRMODE) {
		LUB_MISC_WR &= ~(1 << 4);
	} else if (mode & IR_FIRMODE) {
		LUB_MISC_WR |= 1 << 4;
	}
	pxa2xx_transceiver_mode(dev, mode);
	local_irq_restore(flags);
}