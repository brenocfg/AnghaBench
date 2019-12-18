#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mptsas_portinfo {int num_phys; TYPE_2__* phy_info; } ;
struct mptsas_phyinfo {struct mptsas_portinfo* portinfo; } ;
struct mptsas_devinfo {scalar_t__ sas_address; int /*<<< orphan*/  handle_enclosure; int /*<<< orphan*/  handle_parent; int /*<<< orphan*/  handle; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_8__ {int /*<<< orphan*/  sas_topology_mutex; } ;
struct TYPE_6__ {scalar_t__ sas_address; int /*<<< orphan*/  handle_enclosure; int /*<<< orphan*/  handle_parent; int /*<<< orphan*/  handle; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {TYPE_1__ attached; } ;
typedef  TYPE_3__ MPT_ADAPTER ;

/* Variables and functions */
 struct mptsas_phyinfo* mptsas_find_phyinfo_by_sas_address (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct mptsas_phyinfo *
mptsas_refreshing_device_handles(MPT_ADAPTER *ioc,
	struct mptsas_devinfo *sas_device)
{
	struct mptsas_phyinfo *phy_info;
	struct mptsas_portinfo *port_info;
	int i;

	phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
	    sas_device->sas_address);
	if (!phy_info)
		goto out;
	port_info = phy_info->portinfo;
	if (!port_info)
		goto out;
	mutex_lock(&ioc->sas_topology_mutex);
	for (i = 0; i < port_info->num_phys; i++) {
		if (port_info->phy_info[i].attached.sas_address !=
			sas_device->sas_address)
			continue;
		port_info->phy_info[i].attached.channel = sas_device->channel;
		port_info->phy_info[i].attached.id = sas_device->id;
		port_info->phy_info[i].attached.sas_address =
		    sas_device->sas_address;
		port_info->phy_info[i].attached.handle = sas_device->handle;
		port_info->phy_info[i].attached.handle_parent =
		    sas_device->handle_parent;
		port_info->phy_info[i].attached.handle_enclosure =
		    sas_device->handle_enclosure;
	}
	mutex_unlock(&ioc->sas_topology_mutex);
 out:
	return phy_info;
}