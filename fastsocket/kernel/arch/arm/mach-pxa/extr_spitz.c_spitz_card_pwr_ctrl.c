#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCOOP_CPR ; 
 int /*<<< orphan*/  SPITZ_GPIO_CF_POWER ; 
 int SPITZ_PWR_CF ; 
 int SPITZ_PWR_SD ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned short read_scoop_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ spitzscoop_device ; 
 int /*<<< orphan*/  write_scoop_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void spitz_card_pwr_ctrl(int device, unsigned short new_cpr)
{
	unsigned short cpr = read_scoop_reg(&spitzscoop_device.dev, SCOOP_CPR);

	if (new_cpr & 0x0007) {
		gpio_set_value(SPITZ_GPIO_CF_POWER, 1);
		if (!(cpr & 0x0002) && !(cpr & 0x0004))
		        mdelay(5);
		if (device == SPITZ_PWR_CF)
		        cpr |= 0x0002;
		if (device == SPITZ_PWR_SD)
		        cpr |= 0x0004;
	        write_scoop_reg(&spitzscoop_device.dev, SCOOP_CPR, cpr | new_cpr);
	} else {
		if (device == SPITZ_PWR_CF)
		        cpr &= ~0x0002;
		if (device == SPITZ_PWR_SD)
		        cpr &= ~0x0004;
		if (!(cpr & 0x0002) && !(cpr & 0x0004)) {
			write_scoop_reg(&spitzscoop_device.dev, SCOOP_CPR, 0x0000);
		        mdelay(1);
			gpio_set_value(SPITZ_GPIO_CF_POWER, 0);
		} else {
		        write_scoop_reg(&spitzscoop_device.dev, SCOOP_CPR, cpr | new_cpr);
		}
	}
}