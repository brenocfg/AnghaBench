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
struct image_hdr {int /*<<< orphan*/  imageid; } ;
struct flash_file_hdr_g3 {int /*<<< orphan*/  num_imgs; } ;
struct firmware {int /*<<< orphan*/ * data; } ;
struct be_dma_mem {int size; int /*<<< orphan*/  dma; int /*<<< orphan*/  va; } ;
struct be_cmd_write_flashrom {int dummy; } ;
struct be_adapter {int asic_rev; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UFI_TYPE2 ; 
#define  UFI_TYPE3 130 
#define  UFI_TYPE3R 129 
#define  UFI_TYPE4 128 
 int be_flash_BEx (struct be_adapter*,struct firmware const*,struct be_dma_mem*,int) ; 
 int be_flash_skyhawk (struct be_adapter*,struct firmware const*,struct be_dma_mem*,int) ; 
 int be_get_ufi_type (struct be_adapter*,struct flash_file_hdr_g3*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_fw_download(struct be_adapter *adapter, const struct firmware* fw)
{
	struct flash_file_hdr_g3 *fhdr3;
	struct image_hdr *img_hdr_ptr = NULL;
	struct be_dma_mem flash_cmd;
	const u8 *p;
	int status = 0, i = 0, num_imgs = 0, ufi_type = 0;

	flash_cmd.size = sizeof(struct be_cmd_write_flashrom);
	flash_cmd.va = dma_alloc_coherent(&adapter->pdev->dev, flash_cmd.size,
					  &flash_cmd.dma, GFP_KERNEL);
	if (!flash_cmd.va) {
		status = -ENOMEM;
		goto be_fw_exit;
	}

	p = fw->data;
	fhdr3 = (struct flash_file_hdr_g3 *)p;

	ufi_type = be_get_ufi_type(adapter, fhdr3);

	num_imgs = le32_to_cpu(fhdr3->num_imgs);
	for (i = 0; i < num_imgs; i++) {
		img_hdr_ptr = (struct image_hdr *)(fw->data +
				(sizeof(struct flash_file_hdr_g3) +
				 i * sizeof(struct image_hdr)));
		if (le32_to_cpu(img_hdr_ptr->imageid) == 1) {
			switch (ufi_type) {
			case UFI_TYPE4:
				status = be_flash_skyhawk(adapter, fw,
							&flash_cmd, num_imgs);
				break;
			case UFI_TYPE3R:
				status = be_flash_BEx(adapter, fw, &flash_cmd,
						      num_imgs);
				break;
			case UFI_TYPE3:
				/* Do not flash this ufi on BE3-R cards */
				if (adapter->asic_rev < 0x10)
					status = be_flash_BEx(adapter, fw,
							      &flash_cmd,
							      num_imgs);
				else {
					status = -1;
					dev_err(&adapter->pdev->dev,
						"Can't load BE3 UFI on BE3R\n");
				}
			}
		}
	}

	if (ufi_type == UFI_TYPE2)
		status = be_flash_BEx(adapter, fw, &flash_cmd, 0);
	else if (ufi_type == -1)
		status = -1;

	dma_free_coherent(&adapter->pdev->dev, flash_cmd.size, flash_cmd.va,
			  flash_cmd.dma);
	if (status) {
		dev_err(&adapter->pdev->dev, "Firmware load error\n");
		goto be_fw_exit;
	}

	dev_info(&adapter->pdev->dev, "Firmware flashed successfully\n");

be_fw_exit:
	return status;
}