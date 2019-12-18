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
struct pci_dev {int dummy; } ;
struct nv50_dmac {int /*<<< orphan*/  base; int /*<<< orphan*/  handle; scalar_t__ ptr; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  nv50_chan_destroy (struct nouveau_object*,int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_dmac_destroy(struct nouveau_object *core, struct nv50_dmac *dmac)
{
	if (dmac->ptr) {
		struct pci_dev *pdev = nv_device(core)->pdev;
		pci_free_consistent(pdev, PAGE_SIZE, dmac->ptr, dmac->handle);
	}

	nv50_chan_destroy(core, &dmac->base);
}