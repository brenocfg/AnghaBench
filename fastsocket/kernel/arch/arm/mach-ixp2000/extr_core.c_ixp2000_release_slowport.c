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
struct slowport_cfg {int /*<<< orphan*/  ADC; int /*<<< orphan*/  PCR; int /*<<< orphan*/  RTC; int /*<<< orphan*/  WTC; int /*<<< orphan*/  CCR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXP2000_SLOWPORT_ADC ; 
 int /*<<< orphan*/  IXP2000_SLOWPORT_CCR ; 
 int /*<<< orphan*/  IXP2000_SLOWPORT_PCR ; 
 int /*<<< orphan*/  IXP2000_SLOWPORT_RTC2 ; 
 int /*<<< orphan*/  IXP2000_SLOWPORT_WTC2 ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_slowport_irq_flags ; 
 int /*<<< orphan*/  ixp2000_slowport_lock ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ixp2000_release_slowport(struct slowport_cfg *old_cfg)
{
	ixp2000_reg_write(IXP2000_SLOWPORT_CCR, old_cfg->CCR);
	ixp2000_reg_write(IXP2000_SLOWPORT_WTC2, old_cfg->WTC);
	ixp2000_reg_write(IXP2000_SLOWPORT_RTC2, old_cfg->RTC);
	ixp2000_reg_write(IXP2000_SLOWPORT_PCR, old_cfg->PCR);
	ixp2000_reg_wrb(IXP2000_SLOWPORT_ADC, old_cfg->ADC);

	spin_unlock_irqrestore(&ixp2000_slowport_lock, 
					ixp2000_slowport_irq_flags);
}