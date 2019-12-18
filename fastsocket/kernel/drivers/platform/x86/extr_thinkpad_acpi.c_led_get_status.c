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
typedef  enum led_status_t { ____Placeholder_led_status_t } led_status_t ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
#define  TPACPI_LED_570 128 
 int TPACPI_LED_BLINK ; 
 int TPACPI_LED_OFF ; 
 int TPACPI_LED_ON ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*,int) ; 
 int /*<<< orphan*/  ec_handle ; 
 int led_supported ; 
 int* tpacpi_led_state_cache ; 

__attribute__((used)) static int led_get_status(const unsigned int led)
{
	int status;
	enum led_status_t led_s;

	switch (led_supported) {
	case TPACPI_LED_570:
		if (!acpi_evalf(ec_handle,
				&status, "GLED", "dd", 1 << led))
			return -EIO;
		led_s = (status == 0)?
				TPACPI_LED_OFF :
				((status == 1)?
					TPACPI_LED_ON :
					TPACPI_LED_BLINK);
		tpacpi_led_state_cache[led] = led_s;
		return led_s;
	default:
		return -ENXIO;
	}

	/* not reached */
}