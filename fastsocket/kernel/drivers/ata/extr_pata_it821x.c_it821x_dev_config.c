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
struct ata_device {int* id; int max_sectors; int /*<<< orphan*/  horkage; } ;
typedef  int /*<<< orphan*/  model_num ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_HORKAGE_BROKEN_HPA ; 
 int /*<<< orphan*/  ATA_HORKAGE_DIAGNOSTIC ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  ata_id_c_string (int*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ strstr (unsigned char*,char*) ; 

__attribute__((used)) static void it821x_dev_config(struct ata_device *adev)
{
	unsigned char model_num[ATA_ID_PROD_LEN + 1];

	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, sizeof(model_num));

	if (adev->max_sectors > 255)
		adev->max_sectors = 255;

	if (strstr(model_num, "Integrated Technology Express")) {
		/* RAID mode */
		ata_dev_printk(adev, KERN_INFO, "%sRAID%d volume",
			adev->id[147]?"Bootable ":"",
			adev->id[129]);
		if (adev->id[129] != 1)
			printk("(%dK stripe)", adev->id[146]);
		printk(".\n");
	}
	/* This is a controller firmware triggered funny, don't
	   report the drive faulty! */
	adev->horkage &= ~ATA_HORKAGE_DIAGNOSTIC;
	/* No HPA in 'smart' mode */
	adev->horkage |= ATA_HORKAGE_BROKEN_HPA;
}