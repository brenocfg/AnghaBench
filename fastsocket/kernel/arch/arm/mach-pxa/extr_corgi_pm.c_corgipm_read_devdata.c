#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* machinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio_fatal; int /*<<< orphan*/  gpio_batfull; int /*<<< orphan*/  gpio_batlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORGI_GPIO_AC_IN ; 
 int GPIO_bit (int /*<<< orphan*/ ) ; 
 int GPLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX1111_ACIN_VOLT ; 
 int /*<<< orphan*/  MAX1111_BATT_TEMP ; 
 int /*<<< orphan*/  MAX1111_BATT_VOLT ; 
 unsigned long READ_GPIO_BIT (int /*<<< orphan*/ ) ; 
#define  SHARPSL_ACIN_VOLT 134 
#define  SHARPSL_BATT_TEMP 133 
#define  SHARPSL_BATT_VOLT 132 
#define  SHARPSL_STATUS_ACIN 131 
#define  SHARPSL_STATUS_CHRGFULL 130 
#define  SHARPSL_STATUS_FATAL 129 
#define  SHARPSL_STATUS_LOCK 128 
 TYPE_2__ sharpsl_pm ; 
 unsigned long sharpsl_pm_pxa_read_max1111 (int /*<<< orphan*/ ) ; 

unsigned long corgipm_read_devdata(int type)
{
	switch(type) {
	case SHARPSL_STATUS_ACIN:
		return ((GPLR(CORGI_GPIO_AC_IN) & GPIO_bit(CORGI_GPIO_AC_IN)) != 0);
	case SHARPSL_STATUS_LOCK:
		return READ_GPIO_BIT(sharpsl_pm.machinfo->gpio_batlock);
	case SHARPSL_STATUS_CHRGFULL:
		return READ_GPIO_BIT(sharpsl_pm.machinfo->gpio_batfull);
	case SHARPSL_STATUS_FATAL:
		return READ_GPIO_BIT(sharpsl_pm.machinfo->gpio_fatal);
	case SHARPSL_ACIN_VOLT:
		return sharpsl_pm_pxa_read_max1111(MAX1111_ACIN_VOLT);
	case SHARPSL_BATT_TEMP:
		return sharpsl_pm_pxa_read_max1111(MAX1111_BATT_TEMP);
	case SHARPSL_BATT_VOLT:
	default:
		return sharpsl_pm_pxa_read_max1111(MAX1111_BATT_VOLT);
	}
}