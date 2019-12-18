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
struct fw_desc {int /*<<< orphan*/ * v_addr; int /*<<< orphan*/  p_addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
il_alloc_fw_desc(struct pci_dev *pci_dev, struct fw_desc *desc)
{
	if (!desc->len) {
		desc->v_addr = NULL;
		return -EINVAL;
	}

	desc->v_addr = dma_alloc_coherent(&pci_dev->dev, desc->len,
					  &desc->p_addr, GFP_KERNEL);
	return (desc->v_addr != NULL) ? 0 : -ENOMEM;
}