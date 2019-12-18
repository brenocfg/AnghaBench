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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct locomo_dev {TYPE_5__ dev; } ;
struct TYPE_8__ {int max_brightness; int brightness; } ;
struct TYPE_9__ {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  LOCOMO_GPIO_FL_VR ; 
 int PTR_ERR (TYPE_2__*) ; 
 TYPE_2__* backlight_device_register (char*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  locomo_gpio_set_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locomobl_data ; 
 TYPE_2__* locomolcd_bl_device ; 
 struct locomo_dev* locomolcd_dev ; 
 int /*<<< orphan*/  locomolcd_power (int) ; 
 int /*<<< orphan*/  locomolcd_set_intensity (TYPE_2__*) ; 
 scalar_t__ machine_is_poodle () ; 

__attribute__((used)) static int locomolcd_probe(struct locomo_dev *ldev)
{
	unsigned long flags;

	local_irq_save(flags);
	locomolcd_dev = ldev;

	locomo_gpio_set_dir(ldev->dev.parent, LOCOMO_GPIO_FL_VR, 0);

	/* the poodle_lcd_power function is called for the first time
	 * from fs_initcall, which is before locomo is activated.
	 * We need to recall poodle_lcd_power here*/
	if (machine_is_poodle())
		locomolcd_power(1);

	local_irq_restore(flags);

	locomolcd_bl_device = backlight_device_register("locomo-bl", &ldev->dev, NULL, &locomobl_data);

	if (IS_ERR (locomolcd_bl_device))
		return PTR_ERR (locomolcd_bl_device);

	/* Set up frontlight so that screen is readable */
	locomolcd_bl_device->props.max_brightness = 4,
	locomolcd_bl_device->props.brightness = 2;
	locomolcd_set_intensity(locomolcd_bl_device);

	return 0;
}