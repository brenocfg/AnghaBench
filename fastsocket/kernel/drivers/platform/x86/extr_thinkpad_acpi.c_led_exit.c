#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ name; } ;
struct TYPE_4__ {TYPE_2__ led_classdev; } ;

/* Variables and functions */
 unsigned int TPACPI_LED_NUMLEDS ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_2__*) ; 
 TYPE_1__* tpacpi_leds ; 

__attribute__((used)) static void led_exit(void)
{
	unsigned int i;

	for (i = 0; i < TPACPI_LED_NUMLEDS; i++) {
		if (tpacpi_leds[i].led_classdev.name)
			led_classdev_unregister(&tpacpi_leds[i].led_classdev);
	}

	kfree(tpacpi_leds);
}