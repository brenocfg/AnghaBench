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
struct platform_device {int dummy; } ;
struct mpcore_wdt {int dummy; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_HALT ; 
 scalar_t__ SYSTEM_RESTART ; 
 int /*<<< orphan*/  mpcore_wdt_stop (struct mpcore_wdt*) ; 
 struct mpcore_wdt* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ system_state ; 

__attribute__((used)) static void mpcore_wdt_shutdown(struct platform_device *dev)
{
	struct mpcore_wdt *wdt = platform_get_drvdata(dev);

	if (system_state == SYSTEM_RESTART || system_state == SYSTEM_HALT)
		mpcore_wdt_stop(wdt);
}