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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct fw_desc {scalar_t__ len; int /*<<< orphan*/ * v_addr; int /*<<< orphan*/  p_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
il_free_fw_desc(struct pci_dev *pci_dev, struct fw_desc *desc)
{
	if (desc->v_addr)
		dma_free_coherent(&pci_dev->dev, desc->len, desc->v_addr,
				  desc->p_addr);
	desc->v_addr = NULL;
	desc->len = 0;
}