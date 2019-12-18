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
struct wm8350_led {int /*<<< orphan*/  isink; int /*<<< orphan*/  dcdc; int /*<<< orphan*/  cdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (struct wm8350_led*) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 
 struct wm8350_led* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_led_disable (struct wm8350_led*) ; 

__attribute__((used)) static int wm8350_led_remove(struct platform_device *pdev)
{
	struct wm8350_led *led = platform_get_drvdata(pdev);

	led_classdev_unregister(&led->cdev);
	flush_scheduled_work();
	wm8350_led_disable(led);
	regulator_put(led->dcdc);
	regulator_put(led->isink);
	kfree(led);
	return 0;
}