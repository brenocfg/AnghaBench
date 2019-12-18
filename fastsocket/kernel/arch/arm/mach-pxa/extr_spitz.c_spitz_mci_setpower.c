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
struct pxamci_platform_data {int ocr_mask; } ;
struct device {struct pxamci_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPITZ_PWR_SD ; 
 int /*<<< orphan*/  spitz_card_pwr_ctrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spitz_mci_setpower(struct device *dev, unsigned int vdd)
{
	struct pxamci_platform_data* p_d = dev->platform_data;

	if (( 1 << vdd) & p_d->ocr_mask)
		spitz_card_pwr_ctrl(SPITZ_PWR_SD, 0x0004);
	else
		spitz_card_pwr_ctrl(SPITZ_PWR_SD, 0x0000);
}