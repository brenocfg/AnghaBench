#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t vend_idx; int /*<<< orphan*/  led_state; } ;
typedef  TYPE_1__ hfcusb_data ;
struct TYPE_8__ {scalar_t__ led_scheme; int /*<<< orphan*/ * led_bits; } ;
typedef  TYPE_2__ hfcsusb_vdata ;
struct TYPE_9__ {scalar_t__ driver_info; } ;

/* Variables and functions */
#define  LED_B1_OFF 135 
#define  LED_B1_ON 134 
#define  LED_B2_OFF 133 
#define  LED_B2_ON 132 
 scalar_t__ LED_OFF ; 
#define  LED_POWER_OFF 131 
#define  LED_POWER_ON 130 
#define  LED_S0_OFF 129 
#define  LED_S0_ON 128 
 TYPE_5__* hfcusb_idtab ; 
 int /*<<< orphan*/  set_led_bit (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_led (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_led(hfcusb_data * hfc, int event)
{
	hfcsusb_vdata *driver_info =
	    (hfcsusb_vdata *) hfcusb_idtab[hfc->vend_idx].driver_info;

	/* if no scheme -> no LED action */
	if (driver_info->led_scheme == LED_OFF)
		return;

	switch (event) {
		case LED_POWER_ON:
			set_led_bit(hfc, driver_info->led_bits[0], 1);
			set_led_bit(hfc, driver_info->led_bits[1], 0);
			set_led_bit(hfc, driver_info->led_bits[2], 0);
			set_led_bit(hfc, driver_info->led_bits[3], 0);
			break;
		case LED_POWER_OFF:
			set_led_bit(hfc, driver_info->led_bits[0], 0);
			set_led_bit(hfc, driver_info->led_bits[1], 0);
			set_led_bit(hfc, driver_info->led_bits[2], 0);
			set_led_bit(hfc, driver_info->led_bits[3], 0);
			break;
		case LED_S0_ON:
			set_led_bit(hfc, driver_info->led_bits[1], 1);
			break;
		case LED_S0_OFF:
			set_led_bit(hfc, driver_info->led_bits[1], 0);
			break;
		case LED_B1_ON:
			set_led_bit(hfc, driver_info->led_bits[2], 1);
			break;
		case LED_B1_OFF:
			set_led_bit(hfc, driver_info->led_bits[2], 0);
			break;
		case LED_B2_ON:
			set_led_bit(hfc, driver_info->led_bits[3], 1);
			break;
		case LED_B2_OFF:
			set_led_bit(hfc, driver_info->led_bits[3], 0);
			break;
	}
	write_led(hfc, hfc->led_state);
}