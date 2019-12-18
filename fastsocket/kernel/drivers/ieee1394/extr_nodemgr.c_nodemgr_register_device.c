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
struct device {int /*<<< orphan*/ * class; struct device* parent; } ;
struct unit_directory {struct device device; struct device unit_dev; int /*<<< orphan*/  id; } ;
struct node_entry {struct device device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  memcpy (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nodemgr_create_ud_dev_files (struct unit_directory*) ; 
 int /*<<< orphan*/  nodemgr_dev_template_ud ; 
 int /*<<< orphan*/  nodemgr_ud_class ; 

__attribute__((used)) static void nodemgr_register_device(struct node_entry *ne, 
	struct unit_directory *ud, struct device *parent)
{
	memcpy(&ud->device, &nodemgr_dev_template_ud,
	       sizeof(ud->device));

	ud->device.parent = parent;

	dev_set_name(&ud->device, "%s-%u", dev_name(&ne->device), ud->id);

	ud->unit_dev.parent = &ud->device;
	ud->unit_dev.class = &nodemgr_ud_class;
	dev_set_name(&ud->unit_dev, "%s-%u", dev_name(&ne->device), ud->id);

	if (device_register(&ud->device))
		goto fail_devreg;
	if (device_register(&ud->unit_dev))
		goto fail_classdevreg;
	get_device(&ud->device);

	nodemgr_create_ud_dev_files(ud);

	return;

fail_classdevreg:
	device_unregister(&ud->device);
fail_devreg:
	HPSB_ERR("Failed to create unit %s", dev_name(&ud->device));
}