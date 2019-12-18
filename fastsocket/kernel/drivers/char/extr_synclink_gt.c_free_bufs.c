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
struct slgt_info {int /*<<< orphan*/  pdev; } ;
struct slgt_desc {int /*<<< orphan*/ * buf; int /*<<< orphan*/  buf_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMABUFSIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_bufs(struct slgt_info *info, struct slgt_desc *bufs, int count)
{
	int i;
	for (i=0; i < count; i++) {
		if (bufs[i].buf == NULL)
			continue;
		pci_free_consistent(info->pdev, DMABUFSIZE, bufs[i].buf, bufs[i].buf_dma_addr);
		bufs[i].buf = NULL;
	}
}