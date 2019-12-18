#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wacom {TYPE_4__* intf; TYPE_2__* wacom_wac; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_3__ dev; } ;
struct TYPE_6__ {TYPE_1__* features; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
#define  INTUOS4 134 
#define  INTUOS4L 133 
#define  INTUOS5 132 
#define  INTUOS5L 131 
#define  INTUOS5S 130 
#define  WACOM_21UX2 129 
#define  WACOM_24HD 128 
 int /*<<< orphan*/  cintiq_led_attr_group ; 
 int /*<<< orphan*/  intuos4_led_attr_group ; 
 int /*<<< orphan*/  intuos5_led_attr_group ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wacom_destroy_leds(struct wacom *wacom)
{
	switch (wacom->wacom_wac->features->type) {
	case INTUOS4:
	case INTUOS4L:
		sysfs_remove_group(&wacom->intf->dev.kobj,
				   &intuos4_led_attr_group);
		break;

	case WACOM_24HD:
	case WACOM_21UX2:
		sysfs_remove_group(&wacom->intf->dev.kobj,
				   &cintiq_led_attr_group);
		break;

	case INTUOS5S:
	case INTUOS5:
	case INTUOS5L:
		sysfs_remove_group(&wacom->intf->dev.kobj,
				   &intuos5_led_attr_group);
		break;
	}
}