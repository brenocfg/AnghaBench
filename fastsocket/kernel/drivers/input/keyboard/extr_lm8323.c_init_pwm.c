#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; int /*<<< orphan*/  dev; int /*<<< orphan*/  brightness_set; } ;
struct lm8323_pwm {int id; int running; int enabled; TYPE_1__ cdev; struct lm8323_chip* chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; scalar_t__ desired_brightness; scalar_t__ brightness; scalar_t__ fade_time; } ;
struct lm8323_chip {struct lm8323_pwm* pwm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_time ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  lm8323_pwm_set_brightness ; 
 int /*<<< orphan*/  lm8323_pwm_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_pwm(struct lm8323_chip *lm, int id, struct device *dev,
		    const char *name)
{
	struct lm8323_pwm *pwm;

	BUG_ON(id > 3);

	pwm = &lm->pwm[id - 1];

	pwm->id = id;
	pwm->fade_time = 0;
	pwm->brightness = 0;
	pwm->desired_brightness = 0;
	pwm->running = false;
	pwm->enabled = false;
	INIT_WORK(&pwm->work, lm8323_pwm_work);
	mutex_init(&pwm->lock);
	pwm->chip = lm;

	if (name) {
		pwm->cdev.name = name;
		pwm->cdev.brightness_set = lm8323_pwm_set_brightness;
		if (led_classdev_register(dev, &pwm->cdev) < 0) {
			dev_err(dev, "couldn't register PWM %d\n", id);
			return -1;
		}
		if (device_create_file(pwm->cdev.dev,
					&dev_attr_time) < 0) {
			dev_err(dev, "couldn't register time attribute\n");
			led_classdev_unregister(&pwm->cdev);
			return -1;
		}
		pwm->enabled = true;
	}

	return 0;
}