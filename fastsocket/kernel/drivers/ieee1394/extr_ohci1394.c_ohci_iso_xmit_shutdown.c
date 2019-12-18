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
struct ohci_iso_xmit {int /*<<< orphan*/  prog; scalar_t__ task_active; int /*<<< orphan*/  task; int /*<<< orphan*/  ohci; } ;
struct hpsb_iso {struct ohci_iso_xmit* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_prog_region_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ohci_iso_xmit*) ; 
 int /*<<< orphan*/  ohci1394_unregister_iso_tasklet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_iso_xmit_stop (struct hpsb_iso*) ; 

__attribute__((used)) static void ohci_iso_xmit_shutdown(struct hpsb_iso *iso)
{
	struct ohci_iso_xmit *xmit = iso->hostdata;

	if (xmit->task_active) {
		ohci_iso_xmit_stop(iso);
		ohci1394_unregister_iso_tasklet(xmit->ohci, &xmit->task);
		xmit->task_active = 0;
	}

	dma_prog_region_free(&xmit->prog);
	kfree(xmit);
	iso->hostdata = NULL;
}