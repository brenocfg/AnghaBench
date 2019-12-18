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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_request (int,char*) ; 
 int /*<<< orphan*/  setup_usb (int,int) ; 

__attribute__((used)) static int
evm_u35_setup(struct i2c_client *client, int gpio, unsigned ngpio, void *c)
{
	/* p0 = nDRV_VBUS (initial:  don't supply it) */
	gpio_request(gpio + 0, "nDRV_VBUS");
	gpio_direction_output(gpio + 0, 1);

	/* p1 = VDDIMX_EN */
	gpio_request(gpio + 1, "VDDIMX_EN");
	gpio_direction_output(gpio + 1, 1);

	/* p2 = VLYNQ_EN */
	gpio_request(gpio + 2, "VLYNQ_EN");
	gpio_direction_output(gpio + 2, 1);

	/* p3 = n3V3_CF_RESET (initial: stay in reset) */
	gpio_request(gpio + 3, "nCF_RESET");
	gpio_direction_output(gpio + 3, 0);

	/* (p4 unused) */

	/* p5 = 1V8_WLAN_RESET (initial: stay in reset) */
	gpio_request(gpio + 5, "WLAN_RESET");
	gpio_direction_output(gpio + 5, 1);

	/* p6 = nATA_SEL (initial: select) */
	gpio_request(gpio + 6, "nATA_SEL");
	gpio_direction_output(gpio + 6, 0);

	/* p7 = nCF_SEL (initial: deselect) */
	gpio_request(gpio + 7, "nCF_SEL");
	gpio_direction_output(gpio + 7, 1);

	/* irlml6401 switches over 1A, in under 8 msec;
	 * now it can be managed by nDRV_VBUS ...
	 */
	setup_usb(500, 8);

	return 0;
}