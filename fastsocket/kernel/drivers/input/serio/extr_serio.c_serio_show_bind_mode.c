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
struct serio {scalar_t__ manual_bind; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t serio_show_bind_mode(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct serio *serio = to_serio_port(dev);
	return sprintf(buf, "%s\n", serio->manual_bind ? "manual" : "auto");
}