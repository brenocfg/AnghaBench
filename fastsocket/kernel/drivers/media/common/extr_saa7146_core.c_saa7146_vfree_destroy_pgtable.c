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
struct saa7146_pgtable {int /*<<< orphan*/ * slist; int /*<<< orphan*/  nents; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_sg (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_pgtable_free (struct pci_dev*,struct saa7146_pgtable*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

void saa7146_vfree_destroy_pgtable(struct pci_dev *pci, void *mem, struct saa7146_pgtable *pt)
{
	pci_unmap_sg(pci, pt->slist, pt->nents, PCI_DMA_FROMDEVICE);
	saa7146_pgtable_free(pci, pt);
	kfree(pt->slist);
	pt->slist = NULL;
	vfree(mem);
}