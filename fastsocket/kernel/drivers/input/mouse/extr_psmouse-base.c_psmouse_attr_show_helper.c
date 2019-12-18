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
struct psmouse_attribute {int (* show ) (struct psmouse*,int /*<<< orphan*/ ,char*) ;int /*<<< orphan*/  data; } ;
struct psmouse {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  psmouse_drv ; 
 struct psmouse* serio_get_drvdata (struct serio*) ; 
 int serio_pin_driver (struct serio*) ; 
 int /*<<< orphan*/  serio_unpin_driver (struct serio*) ; 
 int stub1 (struct psmouse*,int /*<<< orphan*/ ,char*) ; 
 struct psmouse_attribute* to_psmouse_attr (struct device_attribute*) ; 
 struct serio* to_serio_port (struct device*) ; 

ssize_t psmouse_attr_show_helper(struct device *dev, struct device_attribute *devattr,
				 char *buf)
{
	struct serio *serio = to_serio_port(dev);
	struct psmouse_attribute *attr = to_psmouse_attr(devattr);
	struct psmouse *psmouse;
	int retval;

	retval = serio_pin_driver(serio);
	if (retval)
		return retval;

	if (serio->drv != &psmouse_drv) {
		retval = -ENODEV;
		goto out;
	}

	psmouse = serio_get_drvdata(serio);

	retval = attr->show(psmouse, attr->data, buf);

out:
	serio_unpin_driver(serio);
	return retval;
}