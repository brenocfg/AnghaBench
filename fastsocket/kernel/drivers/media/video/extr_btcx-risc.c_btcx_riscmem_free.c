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
struct pci_dev {int dummy; } ;
struct btcx_riscmem {scalar_t__ dma; int /*<<< orphan*/ * cpu; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int /*<<< orphan*/  memcnt ; 
 int /*<<< orphan*/  memset (struct btcx_riscmem*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned long) ; 

void btcx_riscmem_free(struct pci_dev *pci,
		       struct btcx_riscmem *risc)
{
	if (NULL == risc->cpu)
		return;
	if (debug) {
		memcnt--;
		printk("btcx: riscmem free [%d] dma=%lx\n",
		       memcnt, (unsigned long)risc->dma);
	}
	pci_free_consistent(pci, risc->size, risc->cpu, risc->dma);
	memset(risc,0,sizeof(*risc));
}