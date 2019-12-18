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
struct seq_file {scalar_t__ private; } ;
struct drm_minor {struct drm_master* master; struct drm_device* dev; } ;
struct drm_master {scalar_t__ unique; } ;
struct drm_info_node {struct drm_minor* minor; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_2__* driver; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {char* (* get_name ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,...) ; 
 char* stub1 (struct drm_device*) ; 

int drm_name_info(struct seq_file *m, void *data)
{
	struct drm_info_node *node = (struct drm_info_node *) m->private;
	struct drm_minor *minor = node->minor;
	struct drm_device *dev = minor->dev;
	struct drm_master *master = minor->master;
	const char *bus_name;
	if (!master)
		return 0;

	bus_name = dev->driver->bus->get_name(dev);
	if (master->unique) {
		seq_printf(m, "%s %s %s\n",
			   bus_name,
			   dev_name(dev->dev), master->unique);
	} else {
		seq_printf(m, "%s %s\n",
			   bus_name, dev_name(dev->dev));
	}
	return 0;
}