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
struct serio {int /*<<< orphan*/ * drv; } ;
struct device {int dummy; } ;
typedef  struct atkbd atkbd ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atkbd_drv ; 
 scalar_t__ serio_get_drvdata (struct serio*) ; 
 int serio_pin_driver (struct serio*) ; 
 int /*<<< orphan*/  serio_unpin_driver (struct serio*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t atkbd_attr_show_helper(struct device *dev, char *buf,
				ssize_t (*handler)(struct atkbd *, char *))
{
	struct serio *serio = to_serio_port(dev);
	int retval;

	retval = serio_pin_driver(serio);
	if (retval)
		return retval;

	if (serio->drv != &atkbd_drv) {
		retval = -ENODEV;
		goto out;
	}

	retval = handler((struct atkbd *)serio_get_drvdata(serio), buf);

out:
	serio_unpin_driver(serio);
	return retval;
}