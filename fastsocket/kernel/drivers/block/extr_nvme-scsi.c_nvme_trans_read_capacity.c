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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int /*<<< orphan*/  ns_id; struct nvme_dev* dev; } ;
struct nvme_id_ns {int dummy; } ;
struct nvme_dev {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GET_READ_CAP_16_ALLOC_LENGTH (scalar_t__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_READ_CAP_16 (scalar_t__*) ; 
 int /*<<< orphan*/  READ_CAP_10_RESP_SIZE ; 
 int /*<<< orphan*/  READ_CAP_16_RESP_SIZE ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_identify (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_trans_fill_read_cap (scalar_t__*,struct nvme_id_ns*,scalar_t__) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_read_capacity(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	u32 alloc_len = READ_CAP_10_RESP_SIZE;
	u32 resp_size = READ_CAP_10_RESP_SIZE;
	u32 xfer_len;
	u8 cdb16;
	struct nvme_dev *dev = ns->dev;
	dma_addr_t dma_addr;
	void *mem;
	struct nvme_id_ns *id_ns;
	u8 *response;

	cdb16 = IS_READ_CAP_16(cmd);
	if (cdb16) {
		alloc_len = GET_READ_CAP_16_ALLOC_LENGTH(cmd);
		resp_size = READ_CAP_16_RESP_SIZE;
	}

	mem = dma_alloc_coherent(&dev->pci_dev->dev, sizeof(struct nvme_id_ns),
							&dma_addr, GFP_KERNEL);
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

	response = kzalloc(resp_size, GFP_KERNEL);
	if (response == NULL) {
		res = -ENOMEM;
		goto out_dma;
	}
	nvme_trans_fill_read_cap(response, id_ns, cdb16);

	xfer_len = min(alloc_len, resp_size);
	res = nvme_trans_copy_to_user(hdr, response, xfer_len);

	kfree(response);
 out_dma:
	dma_free_coherent(&dev->pci_dev->dev, sizeof(struct nvme_id_ns), mem,
			  dma_addr);
 out:
	return res;
}