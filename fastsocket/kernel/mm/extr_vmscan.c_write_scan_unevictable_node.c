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
struct zone {int dummy; } ;
struct sysdev_attribute {int dummy; } ;
struct sys_device {int /*<<< orphan*/  id; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct zone* node_zones; } ;

/* Variables and functions */
 int MAX_NR_ZONES ; 
 TYPE_1__* NODE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populated_zone (struct zone*) ; 
 int /*<<< orphan*/  scan_zone_unevictable_pages (struct zone*) ; 
 unsigned long strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t write_scan_unevictable_node(struct sys_device *dev,
					   struct sysdev_attribute *attr,
					const char *buf, size_t count)
{
	struct zone *node_zones = NODE_DATA(dev->id)->node_zones;
	struct zone *zone;
	unsigned long res;
	unsigned long req = strict_strtoul(buf, 10, &res);

	if (!req)
		return 1;	/* zero is no-op */

	for (zone = node_zones; zone - node_zones < MAX_NR_ZONES; ++zone) {
		if (!populated_zone(zone))
			continue;
		scan_zone_unevictable_pages(zone);
	}
	return 1;
}