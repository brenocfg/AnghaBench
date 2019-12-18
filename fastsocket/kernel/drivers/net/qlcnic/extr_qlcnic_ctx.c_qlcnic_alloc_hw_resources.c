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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_recv_context {struct qlcnic_host_sds_ring* sds_rings; struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_tx_ring {void* desc_head; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/ * hw_consumer; int /*<<< orphan*/  hw_cons_phys_addr; } ;
struct qlcnic_host_sds_ring {void* desc_head; int /*<<< orphan*/  phys_addr; } ;
struct qlcnic_host_rds_ring {void* desc_head; int /*<<< orphan*/  phys_addr; } ;
struct qlcnic_adapter {int max_drv_tx_rings; int max_rds_rings; int max_sds_rings; struct pci_dev* pdev; struct qlcnic_host_tx_ring* tx_ring; struct qlcnic_recv_context* recv_ctx; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCV_DESC_RINGSIZE (struct qlcnic_host_rds_ring*) ; 
 int STATUS_DESC_RINGSIZE (struct qlcnic_host_sds_ring*) ; 
 int TX_DESC_RINGSIZE (struct qlcnic_host_tx_ring*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_hw_resources (struct qlcnic_adapter*) ; 

int qlcnic_alloc_hw_resources(struct qlcnic_adapter *adapter)
{
	void *addr;
	int err, ring;
	struct qlcnic_recv_context *recv_ctx;
	struct qlcnic_host_rds_ring *rds_ring;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_tx_ring *tx_ring;
	__le32 *ptr;

	struct pci_dev *pdev = adapter->pdev;

	recv_ctx = adapter->recv_ctx;

	for (ring = 0; ring < adapter->max_drv_tx_rings; ring++) {
		tx_ring = &adapter->tx_ring[ring];
		ptr = (__le32 *)dma_alloc_coherent(&pdev->dev, sizeof(u32),
						   &tx_ring->hw_cons_phys_addr,
						   GFP_KERNEL);

		if (ptr == NULL) {
			dev_err(&pdev->dev, "failed to allocate tx consumer\n");
			return -ENOMEM;
		}
		tx_ring->hw_consumer = ptr;
		/* cmd desc ring */
		addr = dma_alloc_coherent(&pdev->dev, TX_DESC_RINGSIZE(tx_ring),
					  &tx_ring->phys_addr,
					  GFP_KERNEL);

		if (addr == NULL) {
			dev_err(&pdev->dev,
				"failed to allocate tx desc ring\n");
			err = -ENOMEM;
			goto err_out_free;
		}

		tx_ring->desc_head = addr;
	}

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];
		addr = dma_alloc_coherent(&adapter->pdev->dev,
				RCV_DESC_RINGSIZE(rds_ring),
				&rds_ring->phys_addr, GFP_KERNEL);
		if (addr == NULL) {
			dev_err(&pdev->dev,
				"failed to allocate rds ring [%d]\n", ring);
			err = -ENOMEM;
			goto err_out_free;
		}
		rds_ring->desc_head = addr;

	}

	for (ring = 0; ring < adapter->max_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];

		addr = dma_alloc_coherent(&adapter->pdev->dev,
				STATUS_DESC_RINGSIZE(sds_ring),
				&sds_ring->phys_addr, GFP_KERNEL);
		if (addr == NULL) {
			dev_err(&pdev->dev,
				"failed to allocate sds ring [%d]\n", ring);
			err = -ENOMEM;
			goto err_out_free;
		}
		sds_ring->desc_head = addr;
	}

	return 0;

err_out_free:
	qlcnic_free_hw_resources(adapter);
	return err;
}