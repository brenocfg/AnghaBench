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
struct serio {int dummy; } ;
struct device_driver {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct device_driver* driver_find (char const*,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_driver (struct device_driver*) ; 
 int serio_bind_driver (struct serio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_bus ; 
 int /*<<< orphan*/  serio_disconnect_port (struct serio*) ; 
 int /*<<< orphan*/  serio_find_driver (struct serio*) ; 
 int /*<<< orphan*/  serio_mutex ; 
 int /*<<< orphan*/  serio_reconnect_chain (struct serio*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  to_serio_driver (struct device_driver*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t serio_rebind_driver(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct serio *serio = to_serio_port(dev);
	struct device_driver *drv;
	int error;

	error = mutex_lock_interruptible(&serio_mutex);
	if (error)
		return error;

	if (!strncmp(buf, "none", count)) {
		serio_disconnect_port(serio);
	} else if (!strncmp(buf, "reconnect", count)) {
		serio_reconnect_chain(serio);
	} else if (!strncmp(buf, "rescan", count)) {
		serio_disconnect_port(serio);
		serio_find_driver(serio);
	} else if ((drv = driver_find(buf, &serio_bus)) != NULL) {
		serio_disconnect_port(serio);
		error = serio_bind_driver(serio, to_serio_driver(drv));
		put_driver(drv);
	} else {
		error = -EINVAL;
	}

	mutex_unlock(&serio_mutex);

	return error ? error : count;
}