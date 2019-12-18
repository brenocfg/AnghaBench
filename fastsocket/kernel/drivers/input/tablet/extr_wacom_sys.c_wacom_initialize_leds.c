#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int llv; int hlv; int img_lum; int /*<<< orphan*/ * select; } ;
struct wacom {TYPE_4__* intf; TYPE_3__ led; TYPE_2__* wacom_wac; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_9__ {TYPE_5__ dev; } ;
struct TYPE_7__ {TYPE_1__* features; } ;
struct TYPE_6__ {int type; } ;

/* Variables and functions */
#define  INTUOS4 134 
#define  INTUOS4L 133 
#define  INTUOS5 132 
#define  INTUOS5L 131 
#define  INTUOS5S 130 
#define  WACOM_21UX2 129 
#define  WACOM_24HD 128 
 int /*<<< orphan*/  cintiq_led_attr_group ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  intuos4_led_attr_group ; 
 int /*<<< orphan*/  intuos5_led_attr_group ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wacom_led_control (struct wacom*) ; 

__attribute__((used)) static int wacom_initialize_leds(struct wacom *wacom)
{
	int error;

	/* Initialize default values */
	switch (wacom->wacom_wac->features->type) {
	case INTUOS4:
	case INTUOS4L:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 10;
		wacom->led.hlv = 20;
		wacom->led.img_lum = 10;
		error = sysfs_create_group(&wacom->intf->dev.kobj,
					   &intuos4_led_attr_group);
		break;

	case WACOM_24HD:
	case WACOM_21UX2:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 0;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = sysfs_create_group(&wacom->intf->dev.kobj,
					   &cintiq_led_attr_group);
		break;

	case INTUOS5S:
	case INTUOS5:
	case INTUOS5L:
		wacom->led.select[0] = 0;
		wacom->led.select[1] = 0;
		wacom->led.llv = 32;
		wacom->led.hlv = 0;
		wacom->led.img_lum = 0;

		error = sysfs_create_group(&wacom->intf->dev.kobj,
					   &intuos5_led_attr_group);
		break;

	default:
		return 0;
	}

	if (error) {
		dev_err(&wacom->intf->dev,
			"cannot create sysfs group err: %d\n", error);
		return error;
	}
	wacom_led_control(wacom);

	return 0;
}