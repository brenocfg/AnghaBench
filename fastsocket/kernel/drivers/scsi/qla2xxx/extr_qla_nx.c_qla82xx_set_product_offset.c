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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
struct qla_hw_data {size_t chip_revision; size_t file_prd_off; TYPE_2__* hablob; } ;
struct qla82xx_uri_table_desc {int num_entries; int findex; int entry_size; } ;
typedef  size_t __le32 ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct TYPE_3__ {size_t* data; } ;

/* Variables and functions */
 int QLA82XX_URI_CHIP_REV_OFF ; 
 int /*<<< orphan*/  QLA82XX_URI_DIR_SECT_PRODUCT_TBL ; 
 int QLA82XX_URI_FLAGS_OFF ; 
 size_t cpu_to_le32 (int) ; 
 struct qla82xx_uri_table_desc* qla82xx_get_table_desc (size_t const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_set_product_offset(struct qla_hw_data *ha)
{
	struct qla82xx_uri_table_desc *ptab_desc = NULL;
	const uint8_t *unirom = ha->hablob->fw->data;
	uint32_t i;
	__le32 entries;
	__le32 flags, file_chiprev, offset;
	uint8_t chiprev = ha->chip_revision;
	/* Hardcoding mn_present flag for P3P */
	int mn_present = 0;
	uint32_t flagbit;

	ptab_desc = qla82xx_get_table_desc(unirom,
		 QLA82XX_URI_DIR_SECT_PRODUCT_TBL);
       if (!ptab_desc)
		return -1;

	entries = cpu_to_le32(ptab_desc->num_entries);

	for (i = 0; i < entries; i++) {
		offset = cpu_to_le32(ptab_desc->findex) +
			(i * cpu_to_le32(ptab_desc->entry_size));
		flags = cpu_to_le32(*((int *)&unirom[offset] +
			QLA82XX_URI_FLAGS_OFF));
		file_chiprev = cpu_to_le32(*((int *)&unirom[offset] +
			QLA82XX_URI_CHIP_REV_OFF));

		flagbit = mn_present ? 1 : 2;

		if ((chiprev == file_chiprev) && ((1ULL << flagbit) & flags)) {
			ha->file_prd_off = offset;
			return 0;
		}
	}
	return -1;
}