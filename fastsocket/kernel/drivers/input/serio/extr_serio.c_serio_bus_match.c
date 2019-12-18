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
struct serio_driver {int /*<<< orphan*/  id_table; scalar_t__ manual_bind; } ;
struct serio {scalar_t__ manual_bind; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int serio_match_port (int /*<<< orphan*/ ,struct serio*) ; 
 struct serio_driver* to_serio_driver (struct device_driver*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static int serio_bus_match(struct device *dev, struct device_driver *drv)
{
	struct serio *serio = to_serio_port(dev);
	struct serio_driver *serio_drv = to_serio_driver(drv);

	if (serio->manual_bind || serio_drv->manual_bind)
		return 0;

	return serio_match_port(serio_drv->id_table, serio);
}