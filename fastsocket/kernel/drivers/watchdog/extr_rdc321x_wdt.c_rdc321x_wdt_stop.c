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
struct TYPE_2__ {int /*<<< orphan*/  default_ticks; scalar_t__ running; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__ rdc321x_wdt_device ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int rdc321x_wdt_stop(void)
{
	if (rdc321x_wdt_device.running)
		rdc321x_wdt_device.running = 0;

	ticks = rdc321x_wdt_device.default_ticks;

	return -EIO;
}