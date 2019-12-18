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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct omap_device {TYPE_1__ pdev; } ;

/* Variables and functions */
 int platform_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int omap_device_register(struct omap_device *od)
{
	pr_debug("omap_device: %s: registering\n", od->pdev.name);

	return platform_device_register(&od->pdev);
}