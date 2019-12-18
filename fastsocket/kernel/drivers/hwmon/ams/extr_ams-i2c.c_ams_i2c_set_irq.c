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
typedef  int u8 ;
typedef  enum ams_irq { ____Placeholder_ams_irq } ams_irq ;

/* Variables and functions */
 int /*<<< orphan*/  AMS_CTRLX ; 
 int /*<<< orphan*/  AMS_CTRLY ; 
 int /*<<< orphan*/  AMS_CTRLZ ; 
 int AMS_IRQ_FREEFALL ; 
 int AMS_IRQ_GLOBAL ; 
 int AMS_IRQ_SHOCK ; 
 int ams_i2c_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_i2c_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ams_i2c_set_irq(enum ams_irq reg, char enable)
{
	if (reg & AMS_IRQ_FREEFALL) {
		u8 val = ams_i2c_read(AMS_CTRLX);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_i2c_write(AMS_CTRLX, val);
	}

	if (reg & AMS_IRQ_SHOCK) {
		u8 val = ams_i2c_read(AMS_CTRLY);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_i2c_write(AMS_CTRLY, val);
	}

	if (reg & AMS_IRQ_GLOBAL) {
		u8 val = ams_i2c_read(AMS_CTRLZ);
		if (enable)
			val |= 0x80;
		else
			val &= ~0x80;
		ams_i2c_write(AMS_CTRLZ, val);
	}
}