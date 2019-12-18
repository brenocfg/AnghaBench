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
typedef  int u16 ;
struct nvme_iod {int /*<<< orphan*/  start_time; scalar_t__ nents; int /*<<< orphan*/  sg; struct bio* private; } ;
struct nvme_dev {TYPE_1__* pci_dev; } ;
struct nvme_completion {int /*<<< orphan*/  status; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_end_io_acct (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_free_iod (struct nvme_dev*,struct nvme_iod*) ; 

__attribute__((used)) static void bio_completion(struct nvme_dev *dev, void *ctx,
						struct nvme_completion *cqe)
{
	struct nvme_iod *iod = ctx;
	struct bio *bio = iod->private;
	u16 status = le16_to_cpup(&cqe->status) >> 1;

	if (iod->nents) {
		dma_unmap_sg(&dev->pci_dev->dev, iod->sg, iod->nents,
			bio_data_dir(bio) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		nvme_end_io_acct(bio, iod->start_time);
	}
	nvme_free_iod(dev, iod);
	if (status)
		bio_endio(bio, -EIO);
	else
		bio_endio(bio, 0);
}