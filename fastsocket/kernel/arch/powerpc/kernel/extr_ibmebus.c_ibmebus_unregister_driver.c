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
struct of_platform_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_unregister_driver (struct of_platform_driver*) ; 

void ibmebus_unregister_driver(struct of_platform_driver *drv)
{
	of_unregister_driver(drv);
}