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
typedef  int /*<<< orphan*/  ips_scb_t ;
struct TYPE_7__ {TYPE_3__* scbs; int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_6__ {TYPE_3__* list; } ;
struct TYPE_8__ {int /*<<< orphan*/  scb_busaddr; int /*<<< orphan*/  sg_busaddr; TYPE_1__ sg_list; } ;

/* Variables and functions */
 int IPS_MAX_SG ; 
 int IPS_SGLIST_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_deallocatescbs(ips_ha_t * ha, int cmds)
{
	if (ha->scbs) {
		pci_free_consistent(ha->pcidev,
				    IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * cmds,
				    ha->scbs->sg_list.list,
				    ha->scbs->sg_busaddr);
		pci_free_consistent(ha->pcidev, sizeof (ips_scb_t) * cmds,
				    ha->scbs, ha->scbs->scb_busaddr);
		ha->scbs = NULL;
	}			/* end if */
	return 1;
}