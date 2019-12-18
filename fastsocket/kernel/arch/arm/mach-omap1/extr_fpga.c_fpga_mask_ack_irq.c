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
 int /*<<< orphan*/  fpga_ack_irq (unsigned int) ; 
 int /*<<< orphan*/  fpga_mask_irq (unsigned int) ; 

__attribute__((used)) static void fpga_mask_ack_irq(unsigned int irq)
{
	fpga_mask_irq(irq);
	fpga_ack_irq(irq);
}