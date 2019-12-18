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
struct usb_ov511 {scalar_t__ bridge; scalar_t__ bclass; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 scalar_t__ BRG_OV511PLUS ; 
 int /*<<< orphan*/  PDEBUG (int,char*,char*) ; 
 int /*<<< orphan*/  R511_SYS_LED_CTL ; 
 int /*<<< orphan*/  R518_GPIO_OUT ; 
 int /*<<< orphan*/  reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct usb_ov511*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ov51x_led_control(struct usb_ov511 *ov, int enable)
{
	PDEBUG(4, " (%s)", enable ? "turn on" : "turn off");

	if (ov->bridge == BRG_OV511PLUS)
		reg_w(ov, R511_SYS_LED_CTL, enable ? 1 : 0);
	else if (ov->bclass == BCL_OV518)
		reg_w_mask(ov, R518_GPIO_OUT, enable ? 0x02 : 0x00, 0x02);

	return;
}