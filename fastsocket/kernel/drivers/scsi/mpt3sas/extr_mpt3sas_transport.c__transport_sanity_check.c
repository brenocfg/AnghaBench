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
typedef  scalar_t__ u64 ;
struct _sas_node {int num_phys; TYPE_2__* phy; } ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {scalar_t__ sas_address; } ;
struct TYPE_4__ {int phy_belongs_to_port; TYPE_1__ remote_identify; } ;

/* Variables and functions */
 int /*<<< orphan*/  _transport_del_phy_from_an_existing_port (struct MPT3SAS_ADAPTER*,struct _sas_node*,TYPE_2__*) ; 

__attribute__((used)) static void
_transport_sanity_check(struct MPT3SAS_ADAPTER *ioc, struct _sas_node *sas_node,
	u64 sas_address)
{
	int i;

	for (i = 0; i < sas_node->num_phys; i++) {
		if (sas_node->phy[i].remote_identify.sas_address != sas_address)
			continue;
		if (sas_node->phy[i].phy_belongs_to_port == 1)
			_transport_del_phy_from_an_existing_port(ioc, sas_node,
			    &sas_node->phy[i]);
	}
}