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
 short inw (int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  outw (short,int) ; 

void arch_reset(char mode, const char *cmd)
{
        short temp;
        local_irq_disable();
        /* Reset the Machine via pc[3] of the sequoia chipset */
        outw(0x09,0x24);
        temp=inw(0x26);
        temp = temp | (1<<3) | (1<<10);
        outw(0x09,0x24);
        outw(temp,0x26);
}