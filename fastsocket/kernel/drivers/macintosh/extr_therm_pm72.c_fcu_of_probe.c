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
struct of_device_id {int dummy; } ;
struct of_device {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcu_lookup_fans (int /*<<< orphan*/ ) ; 
 int i2c_add_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  state_detached ; 
 int /*<<< orphan*/  therm_pm72_driver ; 

__attribute__((used)) static int fcu_of_probe(struct of_device* dev, const struct of_device_id *match)
{
	state = state_detached;

	/* Lookup the fans in the device tree */
	fcu_lookup_fans(dev->node);

	/* Add the driver */
	return i2c_add_driver(&therm_pm72_driver);
}