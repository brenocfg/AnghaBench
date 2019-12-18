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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HCI_LCD_BRIGHTNESS ; 
 int HCI_LCD_BRIGHTNESS_SHIFT ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  hci_write1 (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static int set_lcd(int value)
{
	u32 hci_result;

	value = value << HCI_LCD_BRIGHTNESS_SHIFT;
	hci_write1(HCI_LCD_BRIGHTNESS, value, &hci_result);
	if (hci_result != HCI_SUCCESS)
		return -EFAULT;

	return 0;
}