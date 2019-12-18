#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct _diva_dma_map_entry {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/ * object; } ;
struct TYPE_11__ {scalar_t__ registered; int /*<<< orphan*/  irq_nr; } ;
struct TYPE_14__ {int /*<<< orphan*/ * dma_map; scalar_t__ e_max; scalar_t__ Channels; int /*<<< orphan*/ * e_tbl; int /*<<< orphan*/  data_spin_lock; int /*<<< orphan*/  isr_spin_lock; TYPE_8__ isr_soft_isr; TYPE_8__ req_soft_isr; TYPE_1__ irq_info; scalar_t__ Initialized; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdev; int /*<<< orphan*/ ** addr; scalar_t__* bar; } ;
struct TYPE_13__ {TYPE_2__ pci; } ;
struct TYPE_15__ {TYPE_4__ xdi_adapter; TYPE_3__ resources; } ;
typedef  TYPE_5__ diva_os_xdi_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  diva_free_dma_map (int /*<<< orphan*/ ,struct _diva_dma_map_entry*) ; 
 int /*<<< orphan*/  diva_os_cancel_soft_isr (TYPE_8__*) ; 
 int /*<<< orphan*/  diva_os_destroy_spin_lock (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diva_os_remove_irq (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diva_os_remove_soft_isr (TYPE_8__*) ; 
 int /*<<< orphan*/  diva_pri_stop_adapter (TYPE_5__*) ; 
 int /*<<< orphan*/  divasa_unmap_pci_bar (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diva_pri_cleanup_adapter(diva_os_xdi_adapter_t * a)
{
	int bar = 0;

	/*
	   Stop Adapter if adapter is running
	 */
	if (a->xdi_adapter.Initialized) {
		diva_pri_stop_adapter(a);
	}

	/*
	   Remove ISR Handler
	 */
	if (a->xdi_adapter.irq_info.registered) {
		diva_os_remove_irq(a, a->xdi_adapter.irq_info.irq_nr);
	}
	a->xdi_adapter.irq_info.registered = 0;

	/*
	   Step 1: unmap all BAR's, if any was mapped
	 */
	for (bar = 0; bar < 5; bar++) {
		if (a->resources.pci.bar[bar]
		    && a->resources.pci.addr[bar]) {
			divasa_unmap_pci_bar(a->resources.pci.addr[bar]);
			a->resources.pci.bar[bar] = 0;
			a->resources.pci.addr[bar] = NULL;
		}
	}

	/*
	   Free OS objects
	 */
	diva_os_cancel_soft_isr(&a->xdi_adapter.isr_soft_isr);
	diva_os_cancel_soft_isr(&a->xdi_adapter.req_soft_isr);

	diva_os_remove_soft_isr(&a->xdi_adapter.req_soft_isr);
	a->xdi_adapter.isr_soft_isr.object = NULL;

	diva_os_destroy_spin_lock(&a->xdi_adapter.isr_spin_lock, "rm");
	diva_os_destroy_spin_lock(&a->xdi_adapter.data_spin_lock, "rm");

	/*
	   Free memory accupied by XDI adapter
	 */
	if (a->xdi_adapter.e_tbl) {
		diva_os_free(0, a->xdi_adapter.e_tbl);
		a->xdi_adapter.e_tbl = NULL;
	}
	a->xdi_adapter.Channels = 0;
	a->xdi_adapter.e_max = 0;


	/*
	   Free adapter DMA map
	 */
	diva_free_dma_map(a->resources.pci.hdev,
			  (struct _diva_dma_map_entry *) a->xdi_adapter.
			  dma_map);
	a->xdi_adapter.dma_map = NULL;


	/*
	   Detach this adapter from debug driver
	 */

	return (0);
}