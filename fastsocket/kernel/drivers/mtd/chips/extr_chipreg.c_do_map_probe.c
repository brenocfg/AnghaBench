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
struct mtd_info {int dummy; } ;
struct mtd_chip_driver {int /*<<< orphan*/  module; struct mtd_info* (* probe ) (struct map_info*) ;} ;
struct map_info {int dummy; } ;

/* Variables and functions */
 struct mtd_chip_driver* get_mtd_chip_driver (char const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 struct mtd_info* stub1 (struct map_info*) ; 

struct mtd_info *do_map_probe(const char *name, struct map_info *map)
{
	struct mtd_chip_driver *drv;
	struct mtd_info *ret;

	drv = get_mtd_chip_driver(name);

	if (!drv && !request_module("%s", name))
		drv = get_mtd_chip_driver(name);

	if (!drv)
		return NULL;

	ret = drv->probe(map);

	/* We decrease the use count here. It may have been a
	   probe-only module, which is no longer required from this
	   point, having given us a handle on (and increased the use
	   count of) the actual driver code.
	*/
	module_put(drv->module);

	if (ret)
		return ret;

	return NULL;
}