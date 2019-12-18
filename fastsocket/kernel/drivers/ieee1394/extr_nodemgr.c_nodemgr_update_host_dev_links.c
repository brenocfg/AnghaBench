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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct node_entry {TYPE_1__ device; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct hpsb_host {int /*<<< orphan*/  id; int /*<<< orphan*/  node_id; int /*<<< orphan*/  busmgr_id; int /*<<< orphan*/  irm_id; struct device device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPSB_ERR (char*,int /*<<< orphan*/ ) ; 
 struct node_entry* find_entry_by_nodeid (struct hpsb_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void nodemgr_update_host_dev_links(struct hpsb_host *host)
{
	struct device *dev = &host->device;
	struct node_entry *ne;

	sysfs_remove_link(&dev->kobj, "irm_id");
	sysfs_remove_link(&dev->kobj, "busmgr_id");
	sysfs_remove_link(&dev->kobj, "host_id");

	if ((ne = find_entry_by_nodeid(host, host->irm_id)) &&
	    sysfs_create_link(&dev->kobj, &ne->device.kobj, "irm_id"))
		goto fail;
	if ((ne = find_entry_by_nodeid(host, host->busmgr_id)) &&
	    sysfs_create_link(&dev->kobj, &ne->device.kobj, "busmgr_id"))
		goto fail;
	if ((ne = find_entry_by_nodeid(host, host->node_id)) &&
	    sysfs_create_link(&dev->kobj, &ne->device.kobj, "host_id"))
		goto fail;
	return;
fail:
	HPSB_ERR("Failed to update sysfs attributes for host %d", host->id);
}