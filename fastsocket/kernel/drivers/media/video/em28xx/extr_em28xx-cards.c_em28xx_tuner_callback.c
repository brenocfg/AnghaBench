#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tuner_gpio; } ;
struct em28xx {scalar_t__ tuner_type; TYPE_1__ board; } ;

/* Variables and functions */
 scalar_t__ TUNER_XC2028 ; 
 int XC2028_TUNER_RESET ; 
 int em28xx_gpio_set (struct em28xx*,int /*<<< orphan*/ ) ; 

int em28xx_tuner_callback(void *ptr, int component, int command, int arg)
{
	int rc = 0;
	struct em28xx *dev = ptr;

	if (dev->tuner_type != TUNER_XC2028)
		return 0;

	if (command != XC2028_TUNER_RESET)
		return 0;

	rc = em28xx_gpio_set(dev, dev->board.tuner_gpio);

	return rc;
}