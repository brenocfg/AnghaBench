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
 scalar_t__ brstcr ; 
 int /*<<< orphan*/  clrbits8 (scalar_t__,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 

void sbc8560_rstcr_restart(char * cmd)
{
	local_irq_disable();
	if(brstcr)
		clrbits8(brstcr, 0x80);

	while(1);
}