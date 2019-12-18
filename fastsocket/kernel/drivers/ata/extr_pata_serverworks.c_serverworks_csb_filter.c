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
 int ATA_SHIFT_UDMA ; 
 unsigned long ata_bmdma_mode_filter (struct ata_device*,unsigned long) ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 char** csb_bad_ata100 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static unsigned long serverworks_csb_filter(struct ata_device *adev, unsigned long mask)
{
	const char *p;
	char model_num[ATA_ID_PROD_LEN + 1];
	int i;

	/* Disk, UDMA */
	if (adev->class != ATA_DEV_ATA)
		return ata_bmdma_mode_filter(adev, mask);

	/* Actually do need to check */
	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, sizeof(model_num));

	for (i = 0; (p = csb_bad_ata100[i]) != NULL; i++) {
		if (!strcmp(p, model_num))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	return ata_bmdma_mode_filter(adev, mask);
}