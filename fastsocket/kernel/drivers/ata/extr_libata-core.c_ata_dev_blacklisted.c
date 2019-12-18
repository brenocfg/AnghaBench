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
struct ata_device {int /*<<< orphan*/  id; } ;
struct ata_blacklist_entry {unsigned long horkage; int /*<<< orphan*/ * model_rev; int /*<<< orphan*/ * model_num; } ;
typedef  int /*<<< orphan*/  model_rev ;
typedef  int /*<<< orphan*/  model_num ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_ID_FW_REV ; 
 int /*<<< orphan*/  ATA_ID_FW_REV_LEN ; 
 int /*<<< orphan*/  ATA_ID_PROD ; 
 int /*<<< orphan*/  ATA_ID_PROD_LEN ; 
 struct ata_blacklist_entry* ata_device_blacklist ; 
 int /*<<< orphan*/  ata_id_c_string (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strn_pattern_cmp (int /*<<< orphan*/ *,unsigned char*,char) ; 

__attribute__((used)) static unsigned long ata_dev_blacklisted(const struct ata_device *dev)
{
	unsigned char model_num[ATA_ID_PROD_LEN + 1];
	unsigned char model_rev[ATA_ID_FW_REV_LEN + 1];
	const struct ata_blacklist_entry *ad = ata_device_blacklist;

	ata_id_c_string(dev->id, model_num, ATA_ID_PROD, sizeof(model_num));
	ata_id_c_string(dev->id, model_rev, ATA_ID_FW_REV, sizeof(model_rev));

	while (ad->model_num) {
		if (!strn_pattern_cmp(ad->model_num, model_num, '*')) {
			if (ad->model_rev == NULL)
				return ad->horkage;
			if (!strn_pattern_cmp(ad->model_rev, model_rev, '*'))
				return ad->horkage;
		}
		ad++;
	}
	return 0;
}