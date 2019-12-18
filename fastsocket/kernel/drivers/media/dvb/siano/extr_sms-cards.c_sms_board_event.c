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
struct smscore_gpio_config {int dummy; } ;
struct smscore_device_t {int dummy; } ;
typedef  enum SMS_BOARD_EVENTS { ____Placeholder_SMS_BOARD_EVENTS } SMS_BOARD_EVENTS ;

/* Variables and functions */
#define  BOARD_EVENT_BIND 145 
#define  BOARD_EVENT_DEMOD_LOCK 144 
#define  BOARD_EVENT_DEMOD_UNLOCK 143 
#define  BOARD_EVENT_EMERGENCY_WARNING_SIGNAL 142 
#define  BOARD_EVENT_FE_LOCK 141 
#define  BOARD_EVENT_FE_UNLOCK 140 
#define  BOARD_EVENT_MULTIPLEX_ERRORS 139 
#define  BOARD_EVENT_MULTIPLEX_OK 138 
#define  BOARD_EVENT_POWER_INIT 137 
#define  BOARD_EVENT_POWER_RESUME 136 
#define  BOARD_EVENT_POWER_SUSPEND 135 
#define  BOARD_EVENT_RECEPTION_1 134 
#define  BOARD_EVENT_RECEPTION_2 133 
#define  BOARD_EVENT_RECEPTION_3 132 
#define  BOARD_EVENT_RECEPTION_LOST_0 131 
#define  BOARD_EVENT_RECEPTION_MAX_4 130 
#define  BOARD_EVENT_SCAN_COMP 129 
#define  BOARD_EVENT_SCAN_PROG 128 
 int /*<<< orphan*/  sms_err (char*) ; 
 int /*<<< orphan*/  sms_gpio_assign_11xx_default_led_config (struct smscore_gpio_config*) ; 

int sms_board_event(struct smscore_device_t *coredev,
		enum SMS_BOARD_EVENTS gevent) {
	struct smscore_gpio_config MyGpioConfig;

	sms_gpio_assign_11xx_default_led_config(&MyGpioConfig);

	switch (gevent) {
	case BOARD_EVENT_POWER_INIT: /* including hotplug */
		break; /* BOARD_EVENT_BIND */

	case BOARD_EVENT_POWER_SUSPEND:
		break; /* BOARD_EVENT_POWER_SUSPEND */

	case BOARD_EVENT_POWER_RESUME:
		break; /* BOARD_EVENT_POWER_RESUME */

	case BOARD_EVENT_BIND:
		break; /* BOARD_EVENT_BIND */

	case BOARD_EVENT_SCAN_PROG:
		break; /* BOARD_EVENT_SCAN_PROG */
	case BOARD_EVENT_SCAN_COMP:
		break; /* BOARD_EVENT_SCAN_COMP */
	case BOARD_EVENT_EMERGENCY_WARNING_SIGNAL:
		break; /* BOARD_EVENT_EMERGENCY_WARNING_SIGNAL */
	case BOARD_EVENT_FE_LOCK:
		break; /* BOARD_EVENT_FE_LOCK */
	case BOARD_EVENT_FE_UNLOCK:
		break; /* BOARD_EVENT_FE_UNLOCK */
	case BOARD_EVENT_DEMOD_LOCK:
		break; /* BOARD_EVENT_DEMOD_LOCK */
	case BOARD_EVENT_DEMOD_UNLOCK:
		break; /* BOARD_EVENT_DEMOD_UNLOCK */
	case BOARD_EVENT_RECEPTION_MAX_4:
		break; /* BOARD_EVENT_RECEPTION_MAX_4 */
	case BOARD_EVENT_RECEPTION_3:
		break; /* BOARD_EVENT_RECEPTION_3 */
	case BOARD_EVENT_RECEPTION_2:
		break; /* BOARD_EVENT_RECEPTION_2 */
	case BOARD_EVENT_RECEPTION_1:
		break; /* BOARD_EVENT_RECEPTION_1 */
	case BOARD_EVENT_RECEPTION_LOST_0:
		break; /* BOARD_EVENT_RECEPTION_LOST_0 */
	case BOARD_EVENT_MULTIPLEX_OK:
		break; /* BOARD_EVENT_MULTIPLEX_OK */
	case BOARD_EVENT_MULTIPLEX_ERRORS:
		break; /* BOARD_EVENT_MULTIPLEX_ERRORS */

	default:
		sms_err("Unknown SMS board event");
		break;
	}
	return 0;
}