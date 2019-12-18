#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct expander_device {int num_phys; struct ex_phy* ex_phy; } ;
struct ex_phy {scalar_t__ linkrate; scalar_t__ routing_attr; int attached_dev_type; scalar_t__ phy_state; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  attached_phy_id; } ;
struct domain_device {int /*<<< orphan*/  sas_addr; TYPE_3__* port; TYPE_1__* parent; struct expander_device ex_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  fanout_sas_addr; } ;
struct TYPE_6__ {TYPE_2__ disc; int /*<<< orphan*/  sas_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sas_addr; } ;

/* Variables and functions */
 scalar_t__ DIRECT_ROUTING ; 
#define  EDGE_DEV 131 
#define  FANOUT_DEV 130 
 int NO_DEVICE ; 
 scalar_t__ PHY_DEVICE_DISCOVERED ; 
 int /*<<< orphan*/  PHY_FUNC_LINK_RESET ; 
 scalar_t__ PHY_NOT_PRESENT ; 
 scalar_t__ PHY_VACANT ; 
 int SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  SAS_DPRINTK (char*,int,int,...) ; 
#define  SAS_END_DEV 129 
 scalar_t__ SAS_LINK_RATE_UNKNOWN ; 
 scalar_t__ SAS_SATA_SPINUP_HOLD ; 
#define  SATA_PENDING 128 
 scalar_t__ TABLE_ROUTING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_add_parent_port (struct domain_device*,int) ; 
 int /*<<< orphan*/  sas_configure_phy (struct domain_device*,int,int /*<<< orphan*/ ,int) ; 
 int sas_configure_routing (struct domain_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ sas_dev_present_in_domain (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_disable_routing (struct domain_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_ex_disable_phy (struct domain_device*,int) ; 
 int /*<<< orphan*/  sas_ex_disable_port (struct domain_device*,int /*<<< orphan*/ ) ; 
 struct domain_device* sas_ex_discover_end_dev (struct domain_device*,int) ; 
 struct domain_device* sas_ex_discover_expander (struct domain_device*,int) ; 
 scalar_t__ sas_ex_join_wide_port (struct domain_device*,int) ; 
 int sas_ex_phy_discover (struct domain_device*,int) ; 
 int /*<<< orphan*/  sas_smp_phy_control (struct domain_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sas_ex_discover_dev(struct domain_device *dev, int phy_id)
{
	struct expander_device *ex = &dev->ex_dev;
	struct ex_phy *ex_phy = &ex->ex_phy[phy_id];
	struct domain_device *child = NULL;
	int res = 0;

	/* Phy state */
	if (ex_phy->linkrate == SAS_SATA_SPINUP_HOLD) {
		if (!sas_smp_phy_control(dev, phy_id, PHY_FUNC_LINK_RESET, NULL))
			res = sas_ex_phy_discover(dev, phy_id);
		if (res)
			return res;
	}

	/* Parent and domain coherency */
	if (!dev->parent && (SAS_ADDR(ex_phy->attached_sas_addr) ==
			     SAS_ADDR(dev->port->sas_addr))) {
		sas_add_parent_port(dev, phy_id);
		return 0;
	}
	if (dev->parent && (SAS_ADDR(ex_phy->attached_sas_addr) ==
			    SAS_ADDR(dev->parent->sas_addr))) {
		sas_add_parent_port(dev, phy_id);
		if (ex_phy->routing_attr == TABLE_ROUTING)
			sas_configure_phy(dev, phy_id, dev->port->sas_addr, 1);
		return 0;
	}

	if (sas_dev_present_in_domain(dev->port, ex_phy->attached_sas_addr))
		sas_ex_disable_port(dev, ex_phy->attached_sas_addr);

	if (ex_phy->attached_dev_type == NO_DEVICE) {
		if (ex_phy->routing_attr == DIRECT_ROUTING) {
			memset(ex_phy->attached_sas_addr, 0, SAS_ADDR_SIZE);
			sas_configure_routing(dev, ex_phy->attached_sas_addr);
		}
		return 0;
	} else if (ex_phy->linkrate == SAS_LINK_RATE_UNKNOWN)
		return 0;

	if (ex_phy->attached_dev_type != SAS_END_DEV &&
	    ex_phy->attached_dev_type != FANOUT_DEV &&
	    ex_phy->attached_dev_type != EDGE_DEV &&
	    ex_phy->attached_dev_type != SATA_PENDING) {
		SAS_DPRINTK("unknown device type(0x%x) attached to ex %016llx "
			    "phy 0x%x\n", ex_phy->attached_dev_type,
			    SAS_ADDR(dev->sas_addr),
			    phy_id);
		return 0;
	}

	res = sas_configure_routing(dev, ex_phy->attached_sas_addr);
	if (res) {
		SAS_DPRINTK("configure routing for dev %016llx "
			    "reported 0x%x. Forgotten\n",
			    SAS_ADDR(ex_phy->attached_sas_addr), res);
		sas_disable_routing(dev, ex_phy->attached_sas_addr);
		return res;
	}

	if (sas_ex_join_wide_port(dev, phy_id)) {
		SAS_DPRINTK("Attaching ex phy%d to wide port %016llx\n",
			    phy_id, SAS_ADDR(ex_phy->attached_sas_addr));
		return res;
	}

	switch (ex_phy->attached_dev_type) {
	case SAS_END_DEV:
	case SATA_PENDING:
		child = sas_ex_discover_end_dev(dev, phy_id);
		break;
	case FANOUT_DEV:
		if (SAS_ADDR(dev->port->disc.fanout_sas_addr)) {
			SAS_DPRINTK("second fanout expander %016llx phy 0x%x "
				    "attached to ex %016llx phy 0x%x\n",
				    SAS_ADDR(ex_phy->attached_sas_addr),
				    ex_phy->attached_phy_id,
				    SAS_ADDR(dev->sas_addr),
				    phy_id);
			sas_ex_disable_phy(dev, phy_id);
			break;
		} else
			memcpy(dev->port->disc.fanout_sas_addr,
			       ex_phy->attached_sas_addr, SAS_ADDR_SIZE);
		/* fallthrough */
	case EDGE_DEV:
		child = sas_ex_discover_expander(dev, phy_id);
		break;
	default:
		break;
	}

	if (child) {
		int i;

		for (i = 0; i < ex->num_phys; i++) {
			if (ex->ex_phy[i].phy_state == PHY_VACANT ||
			    ex->ex_phy[i].phy_state == PHY_NOT_PRESENT)
				continue;
			/*
			 * Due to races, the phy might not get added to the
			 * wide port, so we add the phy to the wide port here.
			 */
			if (SAS_ADDR(ex->ex_phy[i].attached_sas_addr) ==
			    SAS_ADDR(child->sas_addr)) {
				ex->ex_phy[i].phy_state= PHY_DEVICE_DISCOVERED;
				if (sas_ex_join_wide_port(dev, i))
					SAS_DPRINTK("Attaching ex phy%d to wide port %016llx\n",
						    i, SAS_ADDR(ex->ex_phy[i].attached_sas_addr));

			}
		}
	}

	return res;
}