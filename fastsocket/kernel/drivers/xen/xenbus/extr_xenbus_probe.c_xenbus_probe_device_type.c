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
struct xen_bus_type {int (* probe ) (char const*,char*) ;int /*<<< orphan*/  root; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char**) ; 
 int PTR_ERR (char**) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char**) ; 
 int stub1 (char const*,char*) ; 
 char** xenbus_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int*) ; 

__attribute__((used)) static int xenbus_probe_device_type(struct xen_bus_type *bus, const char *type)
{
	int err = 0;
	char **dir;
	unsigned int dir_n = 0;
	int i;

	dir = xenbus_directory(XBT_NIL, bus->root, type, &dir_n);
	if (IS_ERR(dir))
		return PTR_ERR(dir);

	for (i = 0; i < dir_n; i++) {
		err = bus->probe(type, dir[i]);
		if (err)
			break;
	}
	kfree(dir);
	return err;
}