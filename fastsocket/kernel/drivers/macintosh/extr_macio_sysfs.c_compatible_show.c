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
struct of_device {int /*<<< orphan*/  node; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct of_device ofdev; } ;

/* Variables and functions */
 char* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ sprintf (char*,char*,char const*) ; 
 int strlen (char const*) ; 
 TYPE_1__* to_macio_device (struct device*) ; 

__attribute__((used)) static ssize_t
compatible_show (struct device *dev, struct device_attribute *attr, char *buf)
{
	struct of_device *of;
	const char *compat;
	int cplen;
	int length = 0;

	of = &to_macio_device (dev)->ofdev;
	compat = of_get_property(of->node, "compatible", &cplen);
	if (!compat) {
		*buf = '\0';
		return 0;
	}
	while (cplen > 0) {
		int l;
		length += sprintf (buf, "%s\n", compat);
		buf += length;
		l = strlen (compat) + 1;
		compat += l;
		cplen -= l;
	}

	return length;
}