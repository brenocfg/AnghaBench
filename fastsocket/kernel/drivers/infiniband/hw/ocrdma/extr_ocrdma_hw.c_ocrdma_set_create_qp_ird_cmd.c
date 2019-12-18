#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocrdma_qp {int /*<<< orphan*/  ird_q_va; struct ocrdma_dev* dev; } ;
struct TYPE_4__ {int ird_page_size; int num_ird_pages; scalar_t__ ird; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct ocrdma_dev {TYPE_2__ attr; TYPE_1__ nic_info; } ;
struct ocrdma_create_qp_req {int /*<<< orphan*/ * ird_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_build_q_pages (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocrdma_set_create_qp_ird_cmd(struct ocrdma_create_qp_req *cmd,
					struct ocrdma_qp *qp)
{
	struct ocrdma_dev *dev = qp->dev;
	struct pci_dev *pdev = dev->nic_info.pdev;
	dma_addr_t pa = 0;
	int ird_page_size = dev->attr.ird_page_size;
	int ird_q_len = dev->attr.num_ird_pages * ird_page_size;

	if (dev->attr.ird == 0)
		return 0;

	qp->ird_q_va = dma_alloc_coherent(&pdev->dev, ird_q_len,
					&pa, GFP_KERNEL);
	if (!qp->ird_q_va)
		return -ENOMEM;
	memset(qp->ird_q_va, 0, ird_q_len);
	ocrdma_build_q_pages(&cmd->ird_addr[0], dev->attr.num_ird_pages,
			     pa, ird_page_size);
	return 0;
}