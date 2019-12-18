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
struct b43_wldev {TYPE_1__* wl; } ;
struct b43_leds {int stop; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {struct b43_leds leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void b43_leds_stop(struct b43_wldev *dev)
{
	struct b43_leds *leds = &dev->wl->leds;

	leds->stop = 1;
	cancel_work_sync(&leds->work);
}