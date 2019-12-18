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
typedef  int /*<<< orphan*/  u8 ;
struct c2_mq {int /*<<< orphan*/  host_dma; } ;
struct c2_dev {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_MQ_HOST_TARGET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  c2_mq_rep_init (struct c2_mq*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct c2_mq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c2_alloc_cq_buf(struct c2_dev *c2dev, struct c2_mq *mq, int q_size,
			   int msg_size)
{
	u8 *pool_start;

	pool_start = dma_alloc_coherent(&c2dev->pcidev->dev, q_size * msg_size,
					&mq->host_dma, GFP_KERNEL);
	if (!pool_start)
		return -ENOMEM;

	c2_mq_rep_init(mq,
		       0,		/* index (currently unknown) */
		       q_size,
		       msg_size,
		       pool_start,
		       NULL,	/* peer (currently unknown) */
		       C2_MQ_HOST_TARGET);

	pci_unmap_addr_set(mq, mapping, mq->host_dma);

	return 0;
}