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
struct TYPE_2__ {int /*<<< orphan*/  device_type; int /*<<< orphan*/  target_port_protocols; int /*<<< orphan*/  initiator_port_protocols; int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct domain_device {int dev_type; int /*<<< orphan*/  tproto; int /*<<< orphan*/  iproto; int /*<<< orphan*/  sas_addr; } ;

/* Variables and functions */
#define  EDGE_DEV 132 
#define  FANOUT_DEV 131 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAS_EDGE_EXPANDER_DEVICE ; 
#define  SAS_END_DEV 130 
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_FANOUT_EXPANDER_DEVICE ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
#define  SATA_DEV 129 
#define  SATA_PENDING 128 

__attribute__((used)) static inline void sas_fill_in_rphy(struct domain_device *dev,
				    struct sas_rphy *rphy)
{
	rphy->identify.sas_address = SAS_ADDR(dev->sas_addr);
	rphy->identify.initiator_port_protocols = dev->iproto;
	rphy->identify.target_port_protocols = dev->tproto;
	switch (dev->dev_type) {
	case SATA_DEV:
		/* FIXME: need sata device type */
	case SAS_END_DEV:
	case SATA_PENDING:
		rphy->identify.device_type = SAS_END_DEVICE;
		break;
	case EDGE_DEV:
		rphy->identify.device_type = SAS_EDGE_EXPANDER_DEVICE;
		break;
	case FANOUT_DEV:
		rphy->identify.device_type = SAS_FANOUT_EXPANDER_DEVICE;
		break;
	default:
		rphy->identify.device_type = SAS_PHY_UNUSED;
		break;
	}
}