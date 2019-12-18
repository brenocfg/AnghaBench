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
typedef  size_t u8 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int mode_select_block_len; int /*<<< orphan*/  mode_select_num_blocks; int /*<<< orphan*/  ns_id; struct nvme_dev* dev; } ;
struct nvme_id_ns {int flbas; TYPE_1__* lbaf; int /*<<< orphan*/  ncap; } ;
struct nvme_dev {TYPE_2__* pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int ds; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int nvme_identify (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_fmt_set_blk_size_count(struct nvme_ns *ns,
					     struct sg_io_hdr *hdr)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	struct nvme_dev *dev = ns->dev;
	dma_addr_t dma_addr;
	void *mem;
	struct nvme_id_ns *id_ns;
	u8 flbas;

	/*
	 * SCSI Expects a MODE SELECT would have been issued prior to
	 * a FORMAT UNIT, and the block size and number would be used
	 * from the block descriptor in it. If a MODE SELECT had not
	 * been issued, FORMAT shall use the current values for both.
	 */

	if (ns->mode_select_num_blocks == 0 || ns->mode_select_block_len == 0) {
		mem = dma_alloc_coherent(&dev->pci_dev->dev,
			sizeof(struct nvme_id_ns), &dma_addr, GFP_KERNEL);
		if (mem == NULL) {
			res = -ENOMEM;
			goto out;
		}
		/* nvme ns identify */
		nvme_sc = nvme_identify(dev, ns->ns_id, 0, dma_addr);
		res = nvme_trans_status_code(hdr, nvme_sc);
		if (res)
			goto out_dma;
		if (nvme_sc) {
			res = nvme_sc;
			goto out_dma;
		}
		id_ns = mem;

		if (ns->mode_select_num_blocks == 0)
			ns->mode_select_num_blocks = le64_to_cpu(id_ns->ncap);
		if (ns->mode_select_block_len == 0) {
			flbas = (id_ns->flbas) & 0x0F;
			ns->mode_select_block_len =
						(1 << (id_ns->lbaf[flbas].ds));
		}
 out_dma:
		dma_free_coherent(&dev->pci_dev->dev, sizeof(struct nvme_id_ns),
				  mem, dma_addr);
	}
 out:
	return res;
}