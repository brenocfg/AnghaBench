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

/* Variables and functions */
 int /*<<< orphan*/  ASUS_LED_UNREGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gled ; 
 int /*<<< orphan*/  kled ; 
 int /*<<< orphan*/  led_workqueue ; 
 int /*<<< orphan*/  mled ; 
 int /*<<< orphan*/  pled ; 
 int /*<<< orphan*/  rled ; 
 int /*<<< orphan*/  tled ; 

__attribute__((used)) static void asus_led_exit(void)
{
	destroy_workqueue(led_workqueue);
	ASUS_LED_UNREGISTER(mled);
	ASUS_LED_UNREGISTER(tled);
	ASUS_LED_UNREGISTER(pled);
	ASUS_LED_UNREGISTER(rled);
	ASUS_LED_UNREGISTER(gled);
	ASUS_LED_UNREGISTER(kled);
}