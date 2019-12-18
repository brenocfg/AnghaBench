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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static inline void vxge_os_dma_free(struct pci_dev *pdev, const void *vaddr,
			struct pci_dev **p_dma_acch)
{
	unsigned long misaligned = *(unsigned long *)p_dma_acch;
	u8 *tmp = (u8 *)vaddr;
	tmp -= misaligned;
	kfree((void *)tmp);
}