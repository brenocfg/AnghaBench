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
struct ata_device {scalar_t__ class; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  model_num ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 unsigned long ATA_MASK_MWDMA ; 
 unsigned long ATA_MASK_UDMA ; 
 unsigned long ata_bmdma_mode_filter (struct ata_device*,unsigned long) ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static unsigned long ali_20_filter(struct ata_device *adev, unsigned long mask)
{
	char model_num[ATA_ID_PROD_LEN + 1];
	/* No DMA on anything but a disk for now */
	if (adev->class != ATA_DEV_ATA)
		mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, sizeof(model_num));
	if (strstr(model_num, "WDC"))
		return mask &= ~ATA_MASK_UDMA;
	return ata_bmdma_mode_filter(adev, mask);
}