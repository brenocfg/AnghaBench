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
struct serio_driver {int dummy; } ;
struct serio {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int serio_connect_driver (struct serio*,struct serio_driver*) ; 
 struct serio_driver* to_serio_driver (int /*<<< orphan*/ ) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static int serio_driver_probe(struct device *dev)
{
	struct serio *serio = to_serio_port(dev);
	struct serio_driver *drv = to_serio_driver(dev->driver);

	return serio_connect_driver(serio, drv);
}