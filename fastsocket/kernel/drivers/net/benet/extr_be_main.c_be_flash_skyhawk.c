#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct image_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_images; } ;
struct flash_section_info {TYPE_3__* fsec_entry; TYPE_1__ fsec_hdr; } ;
struct flash_file_hdr_g3 {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;
struct be_dma_mem {int dummy; } ;
struct be_adapter {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  pad_size; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IMAGE_BOOT_CODE 134 
#define  IMAGE_FIRMWARE_BACKUP_iSCSI 133 
#define  IMAGE_FIRMWARE_iSCSI 132 
#define  IMAGE_NCSI 131 
#define  IMAGE_OPTION_ROM_FCoE 130 
#define  IMAGE_OPTION_ROM_ISCSI 129 
#define  IMAGE_OPTION_ROM_PXE 128 
 int OPTYPE_BIOS ; 
 int OPTYPE_FCOE_BIOS ; 
 int OPTYPE_ISCSI_ACTIVE ; 
 int OPTYPE_ISCSI_BACKUP ; 
 int OPTYPE_NCSI_FW ; 
 int OPTYPE_PXE_BIOS ; 
 int OPTYPE_REDBOOT ; 
 int be_flash (struct be_adapter*,int /*<<< orphan*/  const*,struct be_dma_mem*,int,int) ; 
 int be_flash_redboot (struct be_adapter*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct flash_section_info* get_fsec_info (struct be_adapter*,int,struct firmware const*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_flash_skyhawk(struct be_adapter *adapter,
		const struct firmware *fw,
		struct be_dma_mem *flash_cmd, int num_of_images)
{
	int status = 0, i, filehdr_size = 0;
	int img_offset, img_size, img_optype, redboot;
	int img_hdrs_size = num_of_images * sizeof(struct image_hdr);
	const u8 *p = fw->data;
	struct flash_section_info *fsec = NULL;

	filehdr_size = sizeof(struct flash_file_hdr_g3);
	fsec = get_fsec_info(adapter, filehdr_size + img_hdrs_size, fw);
	if (!fsec) {
		dev_err(&adapter->pdev->dev,
			"Invalid Cookie. UFI corrupted ?\n");
		return -1;
	}

	for (i = 0; i < le32_to_cpu(fsec->fsec_hdr.num_images); i++) {
		img_offset = le32_to_cpu(fsec->fsec_entry[i].offset);
		img_size   = le32_to_cpu(fsec->fsec_entry[i].pad_size);

		switch (le32_to_cpu(fsec->fsec_entry[i].type)) {
		case IMAGE_FIRMWARE_iSCSI:
			img_optype = OPTYPE_ISCSI_ACTIVE;
			break;
		case IMAGE_BOOT_CODE:
			img_optype = OPTYPE_REDBOOT;
			break;
		case IMAGE_OPTION_ROM_ISCSI:
			img_optype = OPTYPE_BIOS;
			break;
		case IMAGE_OPTION_ROM_PXE:
			img_optype = OPTYPE_PXE_BIOS;
			break;
		case IMAGE_OPTION_ROM_FCoE:
			img_optype = OPTYPE_FCOE_BIOS;
			break;
		case IMAGE_FIRMWARE_BACKUP_iSCSI:
			img_optype = OPTYPE_ISCSI_BACKUP;
			break;
		case IMAGE_NCSI:
			img_optype = OPTYPE_NCSI_FW;
			break;
		default:
			continue;
		}

		if (img_optype == OPTYPE_REDBOOT) {
			redboot = be_flash_redboot(adapter, fw->data,
					img_offset, img_size,
					filehdr_size + img_hdrs_size);
			if (!redboot)
				continue;
		}

		p = fw->data;
		p += filehdr_size + img_offset + img_hdrs_size;
		if (p + img_size > fw->data + fw->size)
			return -1;

		status = be_flash(adapter, p, flash_cmd, img_optype, img_size);
		if (status) {
			dev_err(&adapter->pdev->dev,
				"Flashing section type %d failed.\n",
				fsec->fsec_entry[i].type);
			return status;
		}
	}
	return 0;
}