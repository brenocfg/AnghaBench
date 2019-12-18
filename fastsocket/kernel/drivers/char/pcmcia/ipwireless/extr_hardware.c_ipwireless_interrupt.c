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
struct ipw_hardware {scalar_t__ hw_version; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ HW_VERSION_1 ; 
 int /*<<< orphan*/  ipwireless_handle_v1_interrupt (int,struct ipw_hardware*) ; 
 int /*<<< orphan*/  ipwireless_handle_v2_v3_interrupt (int,struct ipw_hardware*) ; 

irqreturn_t ipwireless_interrupt(int irq, void *dev_id)
{
	struct ipw_hardware *hw = dev_id;

	if (hw->hw_version == HW_VERSION_1)
		return ipwireless_handle_v1_interrupt(irq, hw);
	else
		return ipwireless_handle_v2_v3_interrupt(irq, hw);
}