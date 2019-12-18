#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uio_portio {int /*<<< orphan*/  kobj; struct uio_port* port; } ;
struct uio_port {scalar_t__ size; struct uio_portio* portio; } ;
struct uio_mem {scalar_t__ size; struct uio_map* map; } ;
struct uio_map {int /*<<< orphan*/  kobj; struct uio_mem* mem; } ;
struct uio_device {TYPE_2__* dev; int /*<<< orphan*/ * map_dir; TYPE_1__* info; int /*<<< orphan*/ * portio_dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {struct uio_mem* mem; struct uio_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int MAX_UIO_MAPS ; 
 int MAX_UIO_PORT_REGIONS ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 void* kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_attr_type ; 
 int /*<<< orphan*/  portio_attr_type ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_attr_grp ; 

__attribute__((used)) static int uio_dev_add_attributes(struct uio_device *idev)
{
	int ret;
	int mi, pi;
	int map_found = 0;
	int portio_found = 0;
	struct uio_mem *mem;
	struct uio_map *map;
	struct uio_port *port;
	struct uio_portio *portio;

	ret = sysfs_create_group(&idev->dev->kobj, &uio_attr_grp);
	if (ret)
		goto err_group;

	for (mi = 0; mi < MAX_UIO_MAPS; mi++) {
		mem = &idev->info->mem[mi];
		if (mem->size == 0)
			break;
		if (!map_found) {
			map_found = 1;
			idev->map_dir = kobject_create_and_add("maps",
							&idev->dev->kobj);
			if (!idev->map_dir)
				goto err_map;
		}
		map = kzalloc(sizeof(*map), GFP_KERNEL);
		if (!map)
			goto err_map;
		kobject_init(&map->kobj, &map_attr_type);
		map->mem = mem;
		mem->map = map;
		ret = kobject_add(&map->kobj, idev->map_dir, "map%d", mi);
		if (ret)
			goto err_map;
		ret = kobject_uevent(&map->kobj, KOBJ_ADD);
		if (ret)
			goto err_map;
	}

	for (pi = 0; pi < MAX_UIO_PORT_REGIONS; pi++) {
		port = &idev->info->port[pi];
		if (port->size == 0)
			break;
		if (!portio_found) {
			portio_found = 1;
			idev->portio_dir = kobject_create_and_add("portio",
							&idev->dev->kobj);
			if (!idev->portio_dir)
				goto err_portio;
		}
		portio = kzalloc(sizeof(*portio), GFP_KERNEL);
		if (!portio)
			goto err_portio;
		kobject_init(&portio->kobj, &portio_attr_type);
		portio->port = port;
		port->portio = portio;
		ret = kobject_add(&portio->kobj, idev->portio_dir,
							"port%d", pi);
		if (ret)
			goto err_portio;
		ret = kobject_uevent(&portio->kobj, KOBJ_ADD);
		if (ret)
			goto err_portio;
	}

	return 0;

err_portio:
	for (pi--; pi >= 0; pi--) {
		port = &idev->info->port[pi];
		portio = port->portio;
		kobject_put(&portio->kobj);
	}
	kobject_put(idev->portio_dir);
err_map:
	for (mi--; mi>=0; mi--) {
		mem = &idev->info->mem[mi];
		map = mem->map;
		kobject_put(&map->kobj);
	}
	kobject_put(idev->map_dir);
	sysfs_remove_group(&idev->dev->kobj, &uio_attr_grp);
err_group:
	dev_err(idev->dev, "error creating sysfs files (%d)\n", ret);
	return ret;
}