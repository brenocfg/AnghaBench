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
struct carm_request {int /*<<< orphan*/  n_elem; int /*<<< orphan*/ * sg; int /*<<< orphan*/  rq; } ;
struct carm_host {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int PCI_DMA_FROMDEVICE ; 
 int PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  carm_end_rq (struct carm_host*,struct carm_request*,int) ; 
 int /*<<< orphan*/  pci_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rq_data_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void carm_handle_rw(struct carm_host *host,
				  struct carm_request *crq, int error)
{
	int pci_dir;

	VPRINTK("ENTER\n");

	if (rq_data_dir(crq->rq) == WRITE)
		pci_dir = PCI_DMA_TODEVICE;
	else
		pci_dir = PCI_DMA_FROMDEVICE;

	pci_unmap_sg(host->pdev, &crq->sg[0], crq->n_elem, pci_dir);

	carm_end_rq(host, crq, error);
}