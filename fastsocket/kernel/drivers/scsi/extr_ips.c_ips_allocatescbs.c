#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ std_list; scalar_t__ enh_list; } ;
struct TYPE_11__ {struct TYPE_11__* q_next; void* sg_busaddr; TYPE_1__ sg_list; void* scb_busaddr; } ;
typedef  TYPE_2__ ips_scb_t ;
struct TYPE_12__ {int max_cmds; TYPE_2__* scb_freelist; TYPE_2__* scbs; int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_3__ ips_ha_t ;
typedef  void* dma_addr_t ;
struct TYPE_13__ {scalar_t__ std_list; scalar_t__ enh_list; int /*<<< orphan*/ * list; } ;
typedef  TYPE_4__ IPS_SG_LIST ;

/* Variables and functions */
 int IPS_MAX_SG ; 
 int IPS_SGLIST_SIZE (TYPE_3__*) ; 
 scalar_t__ IPS_USE_ENH_SGLIST (TYPE_3__*) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,TYPE_2__*,void*) ; 

__attribute__((used)) static int
ips_allocatescbs(ips_ha_t * ha)
{
	ips_scb_t *scb_p;
	IPS_SG_LIST ips_sg;
	int i;
	dma_addr_t command_dma, sg_dma;

	METHOD_TRACE("ips_allocatescbs", 1);

	/* Allocate memory for the SCBs */
	ha->scbs =
	    pci_alloc_consistent(ha->pcidev, ha->max_cmds * sizeof (ips_scb_t),
				 &command_dma);
	if (ha->scbs == NULL)
		return 0;
	ips_sg.list =
	    pci_alloc_consistent(ha->pcidev,
				 IPS_SGLIST_SIZE(ha) * IPS_MAX_SG *
				 ha->max_cmds, &sg_dma);
	if (ips_sg.list == NULL) {
		pci_free_consistent(ha->pcidev,
				    ha->max_cmds * sizeof (ips_scb_t), ha->scbs,
				    command_dma);
		return 0;
	}

	memset(ha->scbs, 0, ha->max_cmds * sizeof (ips_scb_t));

	for (i = 0; i < ha->max_cmds; i++) {
		scb_p = &ha->scbs[i];
		scb_p->scb_busaddr = command_dma + sizeof (ips_scb_t) * i;
		/* set up S/G list */
		if (IPS_USE_ENH_SGLIST(ha)) {
			scb_p->sg_list.enh_list =
			    ips_sg.enh_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		} else {
			scb_p->sg_list.std_list =
			    ips_sg.std_list + i * IPS_MAX_SG;
			scb_p->sg_busaddr =
			    sg_dma + IPS_SGLIST_SIZE(ha) * IPS_MAX_SG * i;
		}

		/* add to the free list */
		if (i < ha->max_cmds - 1) {
			scb_p->q_next = ha->scb_freelist;
			ha->scb_freelist = scb_p;
		}
	}

	/* success */
	return (1);
}