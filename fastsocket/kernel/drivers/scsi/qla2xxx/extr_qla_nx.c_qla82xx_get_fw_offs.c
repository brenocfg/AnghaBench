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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct qla_hw_data {scalar_t__ fw_type; TYPE_2__* hablob; } ;
struct qla82xx_uri_data_desc {int /*<<< orphan*/  findex; } ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t IMAGE_START ; 
 scalar_t__ QLA82XX_UNIFIED_ROMIMAGE ; 
 int /*<<< orphan*/  QLA82XX_URI_DIR_SECT_FW ; 
 int /*<<< orphan*/  QLA82XX_URI_FIRMWARE_IDX_OFF ; 
 size_t cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct qla82xx_uri_data_desc* qla82xx_get_data_desc (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 *
qla82xx_get_fw_offs(struct qla_hw_data *ha)
{
	u32 offset = IMAGE_START;
	struct qla82xx_uri_data_desc *uri_desc = NULL;

	if (ha->fw_type == QLA82XX_UNIFIED_ROMIMAGE) {
		uri_desc = qla82xx_get_data_desc(ha, QLA82XX_URI_DIR_SECT_FW,
			QLA82XX_URI_FIRMWARE_IDX_OFF);
		if (uri_desc)
			offset = cpu_to_le32(uri_desc->findex);
	}

	return (u8 *)&ha->hablob->fw->data[offset];
}